简要说明：如何在本项目中编译 `motor_interface` 草图

推荐方法（VS Code + Arduino 扩展）：
- 在 VS Code 安装 `Arduino` 扩展（Microsoft/Arduino 官方扩展）。
- 打开本工作区，`Arduino` 扩展会读取 `.vscode/arduino.json`，该文件已设置为：
  - 草图：`motor_interface/motor_interface.ino`
  - 板卡：`arduino:avr:mega`（Arduino Mega/ATmega2560）
- 在扩展面板选择正确的串口，然后使用扩展的 `Verify` / `Upload` 功能。
- 默认配置：如果你的 Arduino GUI 安装在 D:\\Users\\User\\AppData\\Local\\Programs\\Arduino IDE，我已把 `.vscode` 中的默认路径指向该目录（`arduino-cli` 可执行文件位置）。

命令行（arduino-cli）：
- 安装并配置 `arduino-cli`，确保已安装 `arduino:avr` 平台及 `mega` 板支持。
- 在工作区根目录运行：

```powershell
arduino-cli compile --fqbn arduino:avr:mega motor_interface
# 上传（示例 COM 口）：
arduino-cli upload -p COM3 --fqbn arduino:avr:mega motor_interface
```

注记：
- 代码引用了 AVR 特定符号（如 `PORTA`, `PA0`）并使用了数字引脚 `22/23`，因此默认目标板为 Arduino Mega（引脚编号适配）。
- 如果你的 Arduino 安装路径不同，请在 `.vscode/c_cpp_properties.json` 中调整 `includePath` 和 `compilerPath`。