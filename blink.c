/**
 * Blink example copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 * Modifications copyright (c) 2021 Brian Starkey <stark3y@gmail.com>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/watchdog.h"
#include "hardware/structs/watchdog.h"

#define ENTRY_MAGIC 0xb105f00d

int main() {
	int flashes = 0;
	const uint LED_PIN = 25;
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	while (flashes < 20) {
		gpio_put(LED_PIN, 1);
		sleep_ms(250);
		gpio_put(LED_PIN, 0);
		sleep_ms(250);
		flashes++;
	}

	hw_clear_bits(&watchdog_hw->ctrl, WATCHDOG_CTRL_ENABLE_BITS);
	watchdog_hw->scratch[5] = ENTRY_MAGIC;
	watchdog_hw->scratch[6] = ~ENTRY_MAGIC;
	watchdog_reboot(0, 0, 0);

	while (1) {
		tight_loop_contents();
	}
}
