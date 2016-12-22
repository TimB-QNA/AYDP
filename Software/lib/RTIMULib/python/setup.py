from distutils.core import setup, Extension
import os.path

RTIMU_sources = [
    "RTMath.cpp",
    "RTIMUHal.cpp",
    "RTIMU.cpp",
    "RTIMUNull.cpp",
    "RTIMUMPU9150.cpp",
    "RTIMUGD20HM303D.cpp",
    "RTIMUGD20M303DLHC.cpp",
    "RTIMULSM9DS0.cpp",
    "RTFusion.cpp",
    "RTFusionKalman4.cpp",
    "RTFusionRTQF.cpp",
    "RTIMUSettings.cpp"
    ]
RTIMU_sourcedir = "../RTIMULib"

mod = Extension('RTIMU',
                sources = ['PyRTIMU.cpp', 'PyRTIMU_Settings.cpp', 'PyRTIMU_RTIMU.cpp'] + 
                  [ os.path.join(RTIMU_sourcedir, sr) for sr in RTIMU_sources],
                include_dirs = [RTIMU_sourcedir],
                extra_compile_args = ['-std=c++0x'],
                define_macros = [("HAL_QUITE", None)]
                )

setup (name = 'RTIMULib',
       version = '1.0',
       description = 'IMU Sensor Fusion Library',
       ext_modules = [mod])
