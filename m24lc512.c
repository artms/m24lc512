/*
 *  EEPROM Microchip 24LC512 compatible module
 */

#include <linux/module.h>
#include <linux/version.h>
#include <linux/kmod.h>

#include <linux/i2c.h>
#include <linux/of_device.h>

#define M24LC512 0

static const struct i2c_device_id m24lc512_idtable[] = {
	{ "24lc512", M24LC512 },
	{ /* END OF LIST */ },
};

// Device Tree matches
static const struct of_device_id m24lc512_of_match[] = {
	{ .compatible = "microchip,24lc512" },
	{ /* END OF LIST */ },
};

static int m24lc512_i2c_probe(struct i2c_client *client)
{
	dev_info(&client->dev, "starting probing\n");
	return 0;
}

static void m24lc512_i2c_remove(struct i2c_client *client)
{
	dev_info(&client->dev, "removing\n");
}

static struct i2c_driver m24lc512_i2c_driver = {
	.driver       = {
		.name = "m24lc512",
		.of_match_table = of_match_ptr(m24lc512_of_match),
	},
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,6,0)
	.probe_new    = m24lc512_i2c_probe,
#else
	.probe        = m24lc512_i2c_probe,
#endif
	.remove       = m24lc512_i2c_remove,
	.id_table     = m24lc512_idtable,
};

static int __init m24lc512_i2c_init(void)
{
	pr_info("module m24lc512 init\n");
	return i2c_add_driver(&m24lc512_i2c_driver);
}
module_init(m24lc512_i2c_init);

static void __exit m24lc512_i2c_exit(void)
{
	pr_info("module m24lc512 exit\n");
	i2c_del_driver(&m24lc512_i2c_driver);
}
module_exit(m24lc512_i2c_exit);

MODULE_AUTHOR("Arturas Moskvinas <arturas.moskvinas@gmail.com>");
MODULE_DESCRIPTION("Microchip 24LC512 EEPROM compatible module");
MODULE_LICENSE("GPL v2");