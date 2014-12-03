#include "power_manager.h"

int main(int argc, char **argv)
{
  struct power_manager_device *device;
  device = udev_manager_init();
 
  printf("Battery charge: %.1f%%\n", ((double)device->charge_now * 100) / device->charge_full);

  if(device != NULL) {
    printf("Freeing power_manager_device!\n");
    free(device);
  }

  return 0;
}
