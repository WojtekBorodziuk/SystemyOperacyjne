# Linux System Monitoring & Security Toolset

## Overview
A collection of custom-built tools designed for Linux system administration, process monitoring, and kernel-level event tracking. These scripts demonstrate a deep understanding of Linux architecture, ranging from user-space automation to kernel-space modules.

## Components

### 1. Port Monitor Daemon (`demon.py`)
A background service (daemon) written in Python that continuously monitors active network connections.
* **Features:** Detaches from the terminal using a double-fork architecture. It uses the `psutil` library to fetch active `inet` connections and logs the local IP and port (`conn.laddr.ip}:{conn.laddr.port}`) to `port_monitor.log` every 10 seconds.

### 2. Disk Space Auditor (`Dyski.sh`)
A Bash script for automated file system and partition monitoring.
* **Features:** Utilizes `lsblk` to list available block devices (disks) and `df -h` to check the storage capacity of a specific partition (`/dev/sda2`). It automatically generates a timestamped report file (e.g., `Report_YYYYMMdd-HHmmss.txt`) containing the system's storage health.

### 3. Kernel-Level Keylogger (`keylogger.c`)
A Proof-of-Concept (PoC) Linux kernel module written in C, demonstrating how malware can intercept hardware interrupts.
* **Features:** Uses the `<linux/keyboard.h>` header and hooks into the kernel's keyboard event stream via `register_keyboard_notifier(&nb)`. When a key is pressed (`action == KBD_KEYCODE`), it captures the raw keycode and writes it directly to the kernel ring buffer using `printk`.

## Disclaimer
*The kernel module (`keylogger.c`) is for educational and authorized testing purposes only.*
