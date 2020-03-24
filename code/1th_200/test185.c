#include <linux/platform_device.h>
#include <linux/gpio_keys.h>
#include <linux/input.h>

struct gpio_keys_button __attribute__((weak)) board_buttons[] = {
	{
		.gpio   = GPIO_PB(31),  //°´¼üÒý½Å
		.code   = KEY_POWER,
		.desc   = "power key",
		.wakeup = 1,
		.debounce_interval = 10,
		.type    = EV_KEY,
		.actiev_low = 1,
	},
};

static struct  gpio_keys_platform_data board_buttons_data = {
	.buttons  = board_buttons,
	.nbuttons = ARRAY_SIZE(board_buttons); 

};

struct platform_device my_button_device = {
	.name = "gpio-keys",
	.id   = -1,
	.num_resource  = 0,
	.dev = {
		.platform_data = &board_buttons_data,
	}

};

static int __init button_base_init(void)
{
	platform_device_register(&my_button_device);
	return 0;
}

arch_initcall(button_base_init);

