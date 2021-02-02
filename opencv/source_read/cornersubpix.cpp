/*
 * @brief Refines the corner locations.
 *        The function iterates to find the sub-pixel accurate location of corners or radial saddle points
 * @param _image input image
 * @param _corners output
 * @param win window size
 * @param zeroZone
 * @param criteria criteria of termination
 *        criteria.type = count || eps, count specifies max count, eps specifies accuracy
 */
void cv::cornerSubPix(InputArray _image, InputOutputArray _corners,
                      Size win, Size zeroZone, TermCriteria criteria) {
    CV_INSTRUMENT_REGION();

    const int MAX_ITERS = 100;
    int win_w = win.width * 2 + 1, win_h = win.height * 2 + 1;
    int i, j, k;
    // use & to speed up
    // type = EPS = 2, 2&1 = 10&01 = 00 = false
    // if type == EPS, use MAX_ITERS
    // type == COUNT, use criteria.maxCount instead
    // still no more than MAX_ITERS
    int max_iters = (criteria.type & CV_TERMCRIT_ITER) ? MIN(MAX(criteria.maxCount, 1), MAX_ITERS) : MAX_ITERS;
    // if type == eps, set eps
    double eps = (criteria.type & CV_TERMCRIT_EPS) ? MAX(criteria.epsilon, 0.) : 0;
    eps *= eps; // use square of error in comparison operations

    cv::Mat src = _image.getMat(), cornersmat = _corners.getMat(); // turn inputArray into Mat
    int count = cornersmat.checkVector(2, CV_32F); // check that the vectors has two cols
    CV_Assert(count >= 0);
    Point2f *corners = cornersmat.ptr<Point2f>();

    if (count == 0)
        return;
    // checks
    CV_Assert(win.width > 0 && win.height > 0); // windows size
    CV_Assert(src.cols >= win.width * 2 + 5 && src.rows >= win.height * 2 + 5); // todo: why add 5?
    CV_Assert(src.channels() == 1); // only gray scale is allowed

    Mat maskm(win_h, win_w, CV_32F), // todo: meaning of maskm
    subpix_buf(win_h + 2, win_w + 2, CV_32F); // tmp for subpixel area
    float *mask = maskm.ptr<float>();

    // init maskm
    for (i = 0; i < win_h; i++) {
        float y = (float) (i - win.height) / win.height; // range: [-1,1]
        float vy = std::exp(-y * y); // exponential
        for (j = 0; j < win_w; j++) {
            float x = (float) (j - win.width) / win.width; // range: [-1,1]
            mask[i * win_w + j] = (float) (vy * std::exp(-x * x)); // exp(-y^2+-x^2) = exp(-r^2) a kind of weight
        }
    }

    // make zero_zone
    if (zeroZone.width >= 0 && zeroZone.height >= 0 &&
        zeroZone.width * 2 + 1 < win_w && zeroZone.height * 2 + 1 < win_h) {
        for (i = win.height - zeroZone.height; i <= win.height + zeroZone.height; i++) {
            for (j = win.width - zeroZone.width; j <= win.width + zeroZone.width; j++) {
                mask[i * win_w + j] = 0; // set the value in zero zone to be zero
            }
        }
    }

    // do optimization loop for all the points
    for (int pt_i = 0; pt_i < count; pt_i++) {
        Point2f cT = corners[pt_i], cI = cT; // the pt_i th point
        int iter = 0;
        double err = 0;

        do {
            Point2f cI2;
            double a = 0, b = 0, c = 0, bb1 = 0, bb2 = 0;

            getRectSubPix(src, Size(win_w + 2, win_h + 2), cI, subpix_buf, subpix_buf.type());
            const float *subpix = &subpix_buf.at<float>(1, 1); // can not change value by ptr

            // process gradient
            for (i = 0, k = 0; i < win_h; i++, subpix += win_w + 2) {
                double py = i - win.height; // pixel y starting from middle

                for (j = 0; j < win_w; j++, k++) {
                    double m = mask[k]; // = i * win_w + j, prevents adding every time
                    double tgx = subpix[j + 1] - subpix[j - 1]; // x change
                    double tgy = subpix[j + win_w + 2] - subpix[j - win_w - 2]; // y change
                    double gxx = tgx * tgx * m;
                    double gxy = tgx * tgy * m;
                    double gyy = tgy * tgy * m;
                    double px = j - win.width; // pixel x starting from middle

                    a += gxx;
                    b += gxy;
                    c += gyy;

                    bb1 += gxx * px + gxy * py;
                    bb2 += gxy * px + gyy * py;
                }
            }
            /**
             * |fxx fxy|
             * |fyx fyy|
             */
            double det = a * c - b * b;
            if (fabs(det) <= DBL_EPSILON * DBL_EPSILON)
                break;

            // 2x2 matrix inversion
            double scale = 1.0 / det;
            cI2.x = (float) (cI.x + c * scale * bb1 - b * scale * bb2);
            cI2.y = (float) (cI.y - b * scale * bb1 + a * scale * bb2);
            err = (cI2.x - cI.x) * (cI2.x - cI.x) + (cI2.y - cI.y) * (cI2.y - cI.y);
            cI = cI2;
            if (cI.x < 0 || cI.x >= src.cols || cI.y < 0 || cI.y >= src.rows)
                break;
        } while (++iter < max_iters && err > eps);

        // if new point is too far from initial, it means poor convergence.
        // leave initial point as the result
        if (fabs(cI.x - cT.x) > win.width || fabs(cI.y - cT.y) > win.height)
            cI = cT;

        corners[pt_i] = cI;
    }
}