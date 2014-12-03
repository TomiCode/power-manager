#include "udev_manager.h"

struct power_manager_device* udev_manager_init()
{
  struct udev *udev;
  struct udev_enumerate *enumerate;
  struct udev_list_entry *devices, *dev_list_entry;
  struct udev_device *device;
  struct udev_monitor *mon;
  struct power_manager_device *new_device = NULL;

  udev = udev_new();
  if(!udev) {
    perror("udev_new");
    exit(1);
  }

  enumerate = udev_enumerate_new(udev);
  udev_enumerate_add_match_subsystem(enumerate, "power_supply");
  udev_enumerate_scan_devices(enumerate);
  devices = udev_enumerate_get_list_entry(enumerate);

  udev_list_entry_foreach(dev_list_entry, devices) {
    const char * path;
    const char * type;

    path = udev_list_entry_get_name(dev_list_entry);
    device = udev_device_new_from_syspath(udev, path);
    type = udev_device_get_sysattr_value(device, "type");
    
    if(strcmp(type, "Battery") == 0) {
      const char * charge_now;
      const char * charge_full;

      charge_now = udev_device_get_sysattr_value(device, "charge_now");
      charge_full = udev_device_get_sysattr_value(device, "charge_full");
      
      if(charge_now == NULL || charge_full == NULL)
      {
        udev_device_unref(device);
        continue;
      }
      new_device = malloc(sizeof(struct power_manager_device));

      new_device->charge_full = (int)strtol(charge_full, NULL, 10);
      new_device->charge_now =  (int)strtol(charge_now , NULL, 10);
      printf("Found Battery [%s]\n", udev_device_get_sysattr_value(device, "manufacturer"));
    }
    udev_device_unref(device);
  }
  udev_enumerate_unref(enumerate);
  return new_device;
}
