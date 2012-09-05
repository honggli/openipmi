/*
 * mcserv.h
 *
 * MontaVista IPMI LAN server include file
 *
 * Author: MontaVista Software, Inc.
 *         Corey Minyard <minyard@mvista.com>
 *         source@mvista.com
 *
 * Copyright 2003,2004,2005 MontaVista Software Inc.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * Lesser General Public License (GPL) Version 2 or the modified BSD
 * license below.  The following disclamer applies to both licenses:
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * GNU Lesser General Public Licence
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2 of
 *  the License, or (at your option) any later version.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Modified BSD Licence
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *   3. The name of the author may not be used to endorse or promote
 *      products derived from this software without specific prior
 *      written permission.
 */

#ifndef __MCSERV_H
#define __MCSERV_H

#include <OpenIPMI/msg.h>

typedef struct lmc_data_s lmc_data_t;

int ipmi_mc_alloc_unconfigured(sys_data_t *sys, unsigned char ipmb,
				  lmc_data_t **rmc);

unsigned char ipmi_mc_get_ipmb(lmc_data_t *mc);
channel_t **ipmi_mc_get_channelset(lmc_data_t *mc);
startcmd_t *ipmi_mc_get_startcmdinfo(lmc_data_t *mc);
user_t *ipmi_mc_get_users(lmc_data_t *mc);
pef_data_t *ipmi_mc_get_pef(lmc_data_t *mc);

void ipmi_mc_destroy(lmc_data_t *mc);

void ipmi_mc_disable(lmc_data_t *mc);
void ipmi_mc_enable(lmc_data_t *mc);

msg_t *ipmi_mc_get_next_recv_q(lmc_data_t *mc);

int ipmi_emu_set_mc_guid(lmc_data_t *mc,
			 unsigned char guid[16],
			 int force);

int ipmi_mc_enable_sel(lmc_data_t    *emu,
		       int           max_entries,
		       unsigned char flags);

int ipmi_mc_add_to_sel(lmc_data_t    *emu,
		       unsigned char record_type,
		       unsigned char event[13],
		       unsigned int  *recid);

int ipmi_mc_add_main_sdr(lmc_data_t    *mc,
			 unsigned char *data,
			 unsigned int  data_len);

int ipmi_mc_add_device_sdr(lmc_data_t    *mc,
			   unsigned char lun,
			   unsigned char *data,
			   unsigned int  data_len);

int ipmi_mc_add_fru_data(lmc_data_t    *mc,
			 unsigned char device_id,
			 unsigned int  length,
			 unsigned char *data,
			 unsigned int  data_len);

int ipmi_mc_get_fru_data(lmc_data_t    *mc,
			 unsigned char device_id,
			 unsigned int  *length,
			 unsigned char **data);

int ipmi_mc_sensor_set_bit(lmc_data_t   *mc,
			   unsigned char lun,
			   unsigned char sens_num,
			   unsigned char bit,
			   unsigned char value,
			   int           gen_event);

int ipmi_mc_sensor_set_bit_clr_rest(lmc_data_t   *mc,
				    unsigned char lun,
				    unsigned char sens_num,
				    unsigned char bit,
				    int           gen_event);

int ipmi_mc_sensor_set_value(lmc_data_t    *mc,
			     unsigned char lun,
			     unsigned char sens_num,
			     unsigned char value,
			     int           gen_event);

int ipmi_mc_sensor_set_hysteresis(lmc_data_t    *mc,
				  unsigned char lun,
				  unsigned char sens_num,
				  unsigned char support,
				  unsigned char positive,
				  unsigned char negative);

int ipmi_mc_sensor_set_threshold(lmc_data_t    *mc,
				 unsigned char lun,
				 unsigned char sens_num,
				 unsigned char support,
				 unsigned char supported[6],
				 unsigned char values[6]);

int ipmi_mc_sensor_set_event_support(lmc_data_t    *mc,
				     unsigned char lun,
				     unsigned char sens_num,
				     unsigned char events_enable,
				     unsigned char scanning,
				     unsigned char support,
				     unsigned char assert_supported[15],
				     unsigned char deassert_supported[15],
				     unsigned char assert_enabled[15],
				     unsigned char deassert_enabled[15]);

int ipmi_mc_add_sensor(lmc_data_t    *mc,
		       unsigned char lun,
		       unsigned char sens_num,
		       unsigned char type,
		       unsigned char event_reading_code);

int ipmi_mc_set_power(lmc_data_t *mc, unsigned char power, int gen_int);

int ipmi_mc_set_num_leds(lmc_data_t   *mc,
			 unsigned int count);

void ipmi_emu_set_device_id(lmc_data_t *emu, unsigned char device_id);
unsigned char ipmi_emu_get_device_id(lmc_data_t *emu);
void ipmi_set_has_device_sdrs(lmc_data_t *emu, unsigned char has_device_sdrs);
unsigned char ipmi_get_has_device_sdrs(lmc_data_t *emu);
void ipmi_set_device_revision(lmc_data_t *emu, unsigned char device_revision);
unsigned char ipmi_get_device_revision(lmc_data_t *emu);
void ipmi_set_major_fw_rev(lmc_data_t *emu, unsigned char major_fw_rev);
unsigned char ipmi_get_major_fw_rev(lmc_data_t *emu);
void ipmi_set_minor_fw_rev(lmc_data_t *emu, unsigned char minor_fw_rev);
unsigned char ipmi_get_minor_fw_rev(lmc_data_t *emu);
void ipmi_set_device_support(lmc_data_t *emu, unsigned char device_support);
unsigned char ipmi_get_device_support(lmc_data_t *emu);
void ipmi_set_mfg_id(lmc_data_t *emu, unsigned char mfg_id[3]);
void ipmi_get_mfg_id(lmc_data_t *emu, unsigned char mfg_id[3]);
void ipmi_set_product_id(lmc_data_t *emu, unsigned char product_id[3]);
void ipmi_get_product_id(lmc_data_t *emu, unsigned char product_id[3]);

void read_persist_users(sys_data_t *sys);
int write_persist_users(sys_data_t *sys);
int ipmi_mc_users_changed(lmc_data_t *mc);

#endif /* __MCSERV_H */