# AGENTS.md

## Cursor Cloud specific instructions

This repo (AF-MDB) is an **embedded hardware + STM32 firmware + MATLAB/Simulink** project, not a
conventional app. There are **no package managers, dependency manifests, dev servers, ports,
databases, automated tests, or lint configs**. Nothing here runs as a long-lived service.

The official toolchain is GUI/licensed and cannot run headless in this VM:

- **Firmware** (`2.Software/MDB-V4.1`, the main project): built with **STM32CubeIDE 1.19.0**
  (Eclipse-managed make; no `Makefile` is committed). Flashing/running needs a physical STM32H7
  board + ST-Link. See `README.md` "编译固件".
- **Simulation** (`3.Simulation/`): **MATLAB/Simulink R2026a** + Embedded Coder. `.slx` models and
  `.mlx` live scripts require MATLAB. See `README.md` "运行仿真".

### What CAN be done headless in this VM

The setup installed two open-source tools (persisted in the VM snapshot; not in the update script):

- **GNU Octave** — runs the plain-text MATLAB parameter scripts. These compute the motor/drive
  model parameters used by the simulation:
  - `octave --no-gui 3.Simulation/code/motor_info/SM060R20B30.m` (or `PM60A3A02030.m`)
  - `octave --no-gui 3.Simulation/code/drive_info/AF_MDB_V4_1.m` (or `_V4_0`, `V3`)
  - Note: the `.mlx` live scripts (e.g. `code/ParameterInit.mlx`) are binary and need real MATLAB;
    Octave can only run the `.m` files above. Set `XDG_RUNTIME_DIR=/tmp/runtime-ubuntu` to silence
    a harmless Qt warning.
- **`arm-none-eabi-gcc`** — the underlying firmware cross-compiler. It compiles the repo's
  HAL/CMSIS driver sources for the target MCU, e.g. from `2.Software/MDB-V4.1`:
  ```
  arm-none-eabi-gcc -c -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb \
    -DUSE_HAL_DRIVER -DSTM32H723xx -DARM_MATH_CM7 \
    -ICore/Inc -IDrivers/STM32H7xx_HAL_Driver/Inc -IDrivers/STM32H7xx_HAL_Driver/Inc/Legacy \
    -IDrivers/CMSIS/Device/ST/STM32H7xx/Include -IDrivers/CMSIS/Include \
    Core/Src/system_stm32h7xx.c -o /tmp/out.o
  ```

### Important gotcha: the application layer cannot be fully built here

The application sources (`App/Foc/app_foc.c`, and anything via `Core/Inc/main.h`) include `FOC.h`
from the Simulink-generated `3.Simulation/FOC_ert_rtw/` directory. **That generated directory is
NOT committed** (despite the README implying it is). A full firmware build therefore requires
regenerating it from `3.Simulation/model/Simulation/ModelRef/FOC.slx` in MATLAB/Embedded Coder
first. Without MATLAB, only the HAL/CMSIS driver layer compiles.
