/*
 * Core MFD support for Cirrus Logic CS35L41 codec
 *
 * Copyright 2017 Cirrus Logic
 *
 * Author:	David Rhodes	<david.rhodes@cirrus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/mfd/core.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#include <sound/cs35l41.h>
#include <linux/mfd/cs35l41/core.h>

static const struct mfd_cell cs35l41_devs[] = {
	{ .name = "cs35l41-codec", },
};

int cs35l41_dev_init(struct cs35l41_data *cs35l41)
{
	int ret;

	dev_set_drvdata(cs35l41->dev, cs35l41);
	dev_info(cs35l41->dev, "Prince MFD core probe\n");

	if (dev_get_platdata(cs35l41->dev))
		memcpy(&cs35l41->pdata, dev_get_platdata(cs35l41->dev),
		       sizeof(cs35l41->pdata));

	ret = mfd_add_devices(cs35l41->dev, PLATFORM_DEVID_NONE, cs35l41_devs,
				ARRAY_SIZE(cs35l41_devs),
				NULL, 0, NULL);
	if (ret) {
		dev_err(cs35l41->dev, "Failed to add subdevices: %d\n", ret);
		return -EINVAL;
	}

	return 0;
}

int cs35l41_dev_exit(struct cs35l41_data *cs35l41)
{
	mfd_remove_devices(cs35l41->dev);
	return 0;
}
