#ifndef H_UDEV_MANAGER
#define H_UDEV_MANAGER

#include "power_manager.h"

struct power_manager_device {
  int status;
  int charge_now;
  int charge_full;
  int online;
};

struct power_manager_device * udev_manager_init(void);

#endif
