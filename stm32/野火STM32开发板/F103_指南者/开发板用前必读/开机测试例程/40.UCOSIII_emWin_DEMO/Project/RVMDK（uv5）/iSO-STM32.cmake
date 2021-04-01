# Made with CMake <> uVision project file synchronizer# https://github.com/bojanpotocnik/cmake-uvision-syncer


# Common definitions
set(DEFINES_COMMON
)

# Assembler specific definitions
set(DEFINES_ASM
	-D
)

# C specific definitions
set(DEFINES_C
	-DSTM32F10X_HD,
	-DUSE_STDPERIPH_DRIVER
)


# Common un-defines
set(UNDEFINES_COMMON
	
)

# Assembler specific un-defines
set(UNDEFINES_ASM
)

# C specific un-defines
set(UNDEFINES_C
)


# Common include directories
set(INCLUDE_DIRS_COMMON
)

# Assembler specific include directories
set(INCLUDE_DIRS_ASM
	.
)

# C specific include directories
set(INCLUDE_DIRS_C
	../../Libraries/CMSIS
	../../User
	../../Libraries/FWlib/inc
	../../uCOS-III/uC-CPU
	../../uCOS-III/uC-CPU/ARM-Cortex-M3/RealView
	../../uCOS-III/uC-LIB
	../../uCOS-III/uC-LIB/Ports/ARM-Cortex-M3/RealView
	../../uCOS-III/uCOS-III/Source
	../../uCOS-III/uCOS-III/Ports/ARM-Cortex-M3/Generic/RealView
	../../User/app
	../../STemWinLibrary522/Config
	../../STemWinLibrary522/inc
	../../ff10
	../../ff10/option
	../../User/os
	../../Mass_Storage/inc
	../../STM32_USB-FS-Device_Driver/inc
)


# Common source files
set(SOURCES_COMMON
)

# Assembler specific source files
set(SOURCES_ASM
	# STARTUP
	../../Libraries/CMSIS/startup/startup_stm32f10x_hd.s
	# uC/CPU
	../../uCOS-III/uC-CPU/ARM-Cortex-M3/RealView/cpu_a.asm
	# uC/LIB
	../../uCOS-III/uC-LIB/Ports/ARM-Cortex-M3/RealView/lib_mem_a.asm
	# uC/Port
	../../uCOS-III/uCOS-III/Ports/ARM-Cortex-M3/Generic/RealView/os_cpu_a.s
)

# C specific source files
set(SOURCES_C
	# CMSIS
	../../Libraries/CMSIS/core_cm3.c
	../../Libraries/CMSIS/system_stm32f10x.c
	# FWLB
	../../Libraries/FWlib/src/misc.c
	../../Libraries/FWlib/src/stm32f10x_adc.c
	../../Libraries/FWlib/src/stm32f10x_bkp.c
	../../Libraries/FWlib/src/stm32f10x_can.c
	../../Libraries/FWlib/src/stm32f10x_cec.c
	../../Libraries/FWlib/src/stm32f10x_crc.c
	../../Libraries/FWlib/src/stm32f10x_dac.c
	../../Libraries/FWlib/src/stm32f10x_dbgmcu.c
	../../Libraries/FWlib/src/stm32f10x_dma.c
	../../Libraries/FWlib/src/stm32f10x_exti.c
	../../Libraries/FWlib/src/stm32f10x_flash.c
	../../Libraries/FWlib/src/stm32f10x_fsmc.c
	../../Libraries/FWlib/src/stm32f10x_gpio.c
	../../Libraries/FWlib/src/stm32f10x_i2c.c
	../../Libraries/FWlib/src/stm32f10x_iwdg.c
	../../Libraries/FWlib/src/stm32f10x_pwr.c
	../../Libraries/FWlib/src/stm32f10x_rcc.c
	../../Libraries/FWlib/src/stm32f10x_rtc.c
	../../Libraries/FWlib/src/stm32f10x_sdio.c
	../../Libraries/FWlib/src/stm32f10x_spi.c
	../../Libraries/FWlib/src/stm32f10x_tim.c
	../../Libraries/FWlib/src/stm32f10x_usart.c
	../../Libraries/FWlib/src/stm32f10x_wwdg.c
	# USER
	../../User/main.c
	../../User/stm32f10x_it.c
	# uC/CPU
	../../uCOS-III/uC-CPU/ARM-Cortex-M3/RealView/cpu_c.c
	../../uCOS-III/uC-CPU/cpu_core.c
	# uC/LIB
	../../uCOS-III/uC-LIB/lib_ascii.c
	../../uCOS-III/uC-LIB/lib_math.c
	../../uCOS-III/uC-LIB/lib_mem.c
	../../uCOS-III/uC-LIB/lib_str.c
	# uC/Source
	../../uCOS-III/uCOS-III/Source/os_cfg_app.c
	../../uCOS-III/uCOS-III/Source/os_core.c
	../../uCOS-III/uCOS-III/Source/os_dbg.c
	../../uCOS-III/uCOS-III/Source/os_flag.c
	../../uCOS-III/uCOS-III/Source/os_int.c
	../../uCOS-III/uCOS-III/Source/os_mem.c
	../../uCOS-III/uCOS-III/Source/os_msg.c
	../../uCOS-III/uCOS-III/Source/os_mutex.c
	../../uCOS-III/uCOS-III/Source/os_pend_multi.c
	../../uCOS-III/uCOS-III/Source/os_prio.c
	../../uCOS-III/uCOS-III/Source/os_q.c
	../../uCOS-III/uCOS-III/Source/os_sem.c
	../../uCOS-III/uCOS-III/Source/os_stat.c
	../../uCOS-III/uCOS-III/Source/os_task.c
	../../uCOS-III/uCOS-III/Source/os_tick.c
	../../uCOS-III/uCOS-III/Source/os_time.c
	../../uCOS-III/uCOS-III/Source/os_tmr.c
	../../uCOS-III/uCOS-III/Source/os_var.c
	# uC/Port
	../../uCOS-III/uCOS-III/Ports/ARM-Cortex-M3/Generic/RealView/os_cpu_c.c
	# BSP
	../../User/bsp/bsp.c
	../../User/bsp/led/bsp_led.c
	../../User/bsp/usart/bsp_usart1.c
	../../User/bsp/lcd/bsp_ili9341_lcd.c
	../../User/bsp/lcd/bsp_xpt2046_lcd.c
	../../User/bsp/spi_flash/fatfs_flash_spi.c
	../../User/bsp/Key/key.c
	../../User/bsp/Beep/beep.c
	../../User/bsp/TouchPad/TouchPad.c
	../../User/bsp/breathinglight/bsp_breathing.c
	../../User/bsp/EEPROM/bsp_i2c_ee.c
	../../User/bsp/EEPROM/bsp_i2c_gpio_ee.c
	../../User/bsp/rtc/bsp_calendar.c
	../../User/bsp/rtc/bsp_date.c
	../../User/bsp/rtc/bsp_rtc.c
	../../User/bsp/ESP8266/bsp_esp8266.c
	../../User/bsp/ov7725/bsp_ov7725.c
	../../User/bsp/ov7725/bsp_sccb.c
	../../User/bsp/sim900a/bsp_usart2.c
	../../User/bsp/sim900a/sim900a.c
	# os_cfg
	../../User/os/os_app_hooks.c
	# app
	../../User/app/app.c
	../../User/app/appicon.c
	../../User/app/Touch_CalibrationApp.c
	../../User/common.c
	../../User/app/KEYapp.c
	../../User/app/Breathingapp.c
	../../User/app/pysearch.c
	../../User/app/keypadapp.c
	../../User/app/ADCapp.c
	../../User/app/EEPROMapp.c
	../../User/app/Clockapp.c
	../../User/app/USBapp.c
	../../User/app/Wifi.c
	../../User/app/Humitureapp.c
	../../User/app/Cameraapp.c
	../../User/app/Calculatorapp.c
	../../User/app/Phoneapp.c
	../../User/app/Messageapp.c
	../../User/app/UserApp.c
	# STemWin_V522
	../../STemWinLibrary522/Config/GUIConf.c
	../../STemWinLibrary522/Config/LCDConf_FlexColor_Template.c
	../../STemWinLibrary522/OS/GUI_X_uCOS.c
	../../STemWinLibrary522/OS/GUI_X_Touch_Analog.c
	# ff10
	../../ff10/diskio.c
	../../ff10/ff.c
	../../ff10/firecc936.c
	# STM32_USB-FS-Device_Driver
	../../STM32_USB-FS-Device_Driver/src/usb_core.c
	../../STM32_USB-FS-Device_Driver/src/usb_init.c
	../../STM32_USB-FS-Device_Driver/src/usb_int.c
	../../STM32_USB-FS-Device_Driver/src/usb_mem.c
	../../STM32_USB-FS-Device_Driver/src/usb_regs.c
	../../STM32_USB-FS-Device_Driver/src/usb_sil.c
	# Mass_Storage
	../../Mass_Storage/src/hw_config.c
	../../Mass_Storage/src/mass_mal.c
	../../Mass_Storage/src/memory.c
	../../Mass_Storage/src/scsi_data.c
	../../Mass_Storage/src/usb_bot.c
	../../Mass_Storage/src/usb_desc.c
	../../Mass_Storage/src/usb_endp.c
	../../Mass_Storage/src/usb_istr.c
	../../Mass_Storage/src/usb_prop.c
	../../Mass_Storage/src/usb_pwr.c
	../../Mass_Storage/src/usb_scsi.c
)


# Other files
set(OTHER_FILES
	# CMSIS
	../../Libraries/CMSIS/core_cm3.h
	../../Libraries/CMSIS/stm32f10x.h
	../../Libraries/CMSIS/system_stm32f10x.h
	# USER
	../../User/stm32f10x_conf.h
	../../User/stm32f10x_it.h
	# DOC
	../../Doc/readme.txt
	# uC/CPU
	../../uCOS-III/uC-CPU/ARM-Cortex-M3/RealView/cpu.h
	../../uCOS-III/uC-CPU/cpu_core.h
	../../uCOS-III/uC-CPU/cpu_def.h
	# uC/LIB
	../../uCOS-III/uC-LIB/lib_ascii.h
	../../uCOS-III/uC-LIB/lib_def.h
	../../uCOS-III/uC-LIB/lib_math.h
	../../uCOS-III/uC-LIB/lib_mem.h
	../../uCOS-III/uC-LIB/lib_str.h
	# uC/Source
	../../uCOS-III/uCOS-III/Source/os.h
	../../uCOS-III/uCOS-III/Source/os_type.h
	# uC/Port
	../../uCOS-III/uCOS-III/Ports/ARM-Cortex-M3/Generic/RealView/os_cpu.h
	# os_cfg
	../../User/os/app_cfg.h
	../../User/os/cpu_cfg.h
	../../User/os/lib_cfg.h
	../../User/os/os_app_hooks.h
	../../User/os/os_cfg.h
	../../User/os/os_cfg_app.h
	# app
	../../User/includes.h
	../../User/app/app.h
)
