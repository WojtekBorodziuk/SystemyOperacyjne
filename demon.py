import psutil
import time
import os
import sys
import logging

logging.basicConfig(
    filename='port_monitor.log',
    level=logging.INFO,
    format='%(asctime)s - %(message)s'
)


def log_open_ports():
    while True:

        connections = psutil.net_connections(kind='inet')

        for conn in connections:
            local_address = f"{conn.laddr.ip}:{conn.laddr.port}"
            logging.info(f"Open port: {local_address}")

        time.sleep(10)


def daemonize():
    if os.fork() > 0:
        sys.exit()

    os.setsid()

    if os.fork() > 0:
        sys.exit()

    os.chdir("/")
    os.umask(0)
    sys.stdout.flush()
    sys.stderr.flush()
    with open(os.devnull, 'r') as devnull:
        os.dup2(devnull.fileno(), sys.stdin.fileno())
    with open('port_monitor.log', 'a+') as devnull:
        os.dup2(devnull.fileno(), sys.stdout.fileno())
        os.dup2(devnull.fileno(), sys.stderr.fileno())

    log_open_ports()


if __name__ == "__main__":
    daemonize()