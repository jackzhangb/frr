/* Zebra Mlag Code.
 * Copyright (C) 2018 Cumulus Networks, Inc.
 *                    Donald Sharp
 *
 * This file is part of FRR.
 *
 * FRR is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * FRR is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FRR; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */
#include "zebra.h"

#include "command.h"
#include "hook.h"

#include "zebra/zebra_mlag.h"

#ifndef VTYSH_EXTRACT_PL
#include "zebra/zebra_mlag_clippy.c"
#endif

enum mlag_role role = MLAG_ROLE_NONE;

enum mlag_role zebra_mlag_get_role(void)
{
	return role;
}

DEFUN_HIDDEN (show_mlag,
	      show_mlag_cmd,
	      "show zebra mlag",
	      SHOW_STR
	      ZEBRA_STR
	      "The mlag role on this machine\n")
{
	char buf[80];

	vty_out(vty, "MLag is configured to: %s\n",
		mlag_role2str(role, buf, sizeof(buf)));

	return CMD_SUCCESS;
}

DEFPY_HIDDEN (test_mlag,
	      test_mlag_cmd,
	      "test zebra mlag <none$none|primary$primary|secondary$secondary>",
	      "Test code\n"
	      ZEBRA_STR
	      "Modify the Mlag state\n"
	      "Mlag is not setup on the machine\n"
	      "Mlag is setup to be primary\n"
	      "Mlag is setup to be the secondary\n")
{
	if (none)
		role = MLAG_ROLE_NONE;
	if (primary)
		role = MLAG_ROLE_PRIMARY;
	if (secondary)
		role = MLAG_ROLE_SECONDARY;

	return CMD_SUCCESS;
}

void zebra_mlag_init(void)
{
	install_element(VIEW_NODE, &show_mlag_cmd);
	install_element(ENABLE_NODE, &test_mlag_cmd);
}

void zebra_mlag_terminate(void)
{
}
