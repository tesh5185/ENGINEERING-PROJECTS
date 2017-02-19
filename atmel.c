#include <asf.h>
#include "platform.h"
#include "at_ble_api.h"
#include "console_serial.h"
#include "timer_hw.h"
#include "ble_manager.h"
#include "ble_utils.h"
#include "button.h"
#include "startup_template_app.h"
#include "at_ble_trace.h"
#include "at_ble_errno.h"
#include "pas_client.h"
#include "pas_app.h"

volatile uint8_t press_count = DEVICE_SILENT;		/*!< button press count*/
volatile bool flag = false;					/*!< To send values once per button press*/
volatile bool app_state;			/*!< state of the app,true for connected false for disconnected*/
volatile at_ble_status_t status;
at_ble_handle_t htpt_conn_handle;
volatile bool Timer_Flag = false;
volatile bool Temp_Notification_Flag = false;


static at_ble_status_t ble_paired_cb (void *param);
static at_ble_status_t ble_disconnected_cb (void *param);

static const ble_event_callback_t app_gap_handle[] = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	app_connected_event_handler,
	app_disconnected_event_handler,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};
void button_cb(void);
static void display_alert_status_info(uint8_t *data)
{
	if (data[0] & BIT0_MASK) {
		DBG_LOG("Ringer State Active");
		} else {
		DBG_LOG("Ringer State Inactive");
	}
	
	if (data[0] & BIT1_MASK) {
		DBG_LOG("Vibration State Active");
		} else {
		DBG_LOG("Vibration State Inactive");
	}
	
	if (data[0] & BIT2_MASK) {
		DBG_LOG("Display State Active");
		} else {
		DBG_LOG("Display State Inactive");
	}
}
static void display_ringer_setting_info(uint8_t *data)
{
	if (data[0] == RINGER_SILENT) {
		DBG_LOG_CONT("Ringer Silent");
		} else if (data[0] == RINGER_NORMAL) {
		DBG_LOG_CONT("Ringer Normal");
	}
}

static at_ble_status_t app_connected_event_handler(void *params)
{
	app_state = true;
	ALL_UNUSED(params);
	return AT_BLE_SUCCESS;
}
static at_ble_status_t app_disconnected_event_handler(void *params)
{
	app_state = false;
	press_count = DEVICE_SILENT;
	//pas_client_adv();
	//ALL_UNUSED(params);
    ble_advertise();
	return AT_BLE_SUCCESS;
}

static void app_alert_status_read(uint8_t *data, uint8_t len)
{
	DBG_LOG("\r\nAlert Status read:");
	DBG_LOG_DEV("Length of the data is %d",len);
	display_alert_status_info(data);
}

static void app_ringer_setting_read(uint8_t *data, uint8_t len)
{
	DBG_LOG("\r\nRinger setting read :");
	DBG_LOG_DEV("Length of the data is %d",len);
	display_ringer_setting_info(data);
}
static void app_alert_status_notify(uint8_t *data, uint8_t len)
{
	DBG_LOG("\r\nNotified Alert Status :");
	DBG_LOG_DEV("length of the data is %d",len);
	display_alert_status_info(data);
}
static void app_ringer_setting_notify(uint8_t *data, uint8_t len)
{
	DBG_LOG("\r\nNotified Ringer setting :");
	DBG_LOG_DEV("length of the data is %d",len);
	display_ringer_setting_info(data);
}

void button_cb(void)
{
	if (app_state && !flag) {
		flag = true;
		send_plf_int_msg_ind(USER_TIMER_CALLBACK, TIMER_EXPIRED_CALLBACK_TYPE_DETECT, NULL, 0);
	}
}







static void ble_advertise (void)
{
	printf("\nAssignment 2.1 : Start Advertising");
	status = ble_advertisement_data_set();
	if(status != AT_BLE_SUCCESS)
	{
		printf("\n\r## Advertisement data set failed : error %x",status);
		while(1);
	}
	/* Start of advertisement */
	status = at_ble_adv_start(AT_BLE_ADV_TYPE_UNDIRECTED,\
	AT_BLE_ADV_GEN_DISCOVERABLE,\
	NULL,\
	AT_BLE_ADV_FP_ANY,\
	1000,\
	655,\
	0);
	if(status != AT_BLE_SUCCESS)
	{
		printf("\n\r## Advertisement data set failed : error %x",status);
		while(1);
	}
}


static void htp_temperature_read(void)
{
	float temperature;
	/* Read Temperature Value from IO1 Xplained Pro */
	temperature = at30tse_read_temperature();
	/* Display temperature on com port */
	#ifdef HTPT_FAHRENHEIT
	printf("\nTemperature: %d Fahrenheit", (uint16_t)temperature);
	#else
	printf("\nTemperature: %d Deg Celsius", (uint16_t)temperature);
	#endif
}

/* Callback registered for AT_BLE_CONNECTED event*/
static at_ble_status_t ble_paired_cb (void *param)
{
	at_ble_pair_done_t *pair_params = param;
	printf("\nAssignment 3.2: Application paired ");
	/* Enable the HTP Profile */
	printf("\nAssignment 4.1: enable health temperature service ");
	status = at_ble_htpt_enable(pair_params->handle,
	HTPT_CFG_INTERM_MEAS_NTF);
	if(status != AT_BLE_SUCCESS){
		printf("*** Failure in HTP Profile Enable");
		while(true);
	}
	ALL_UNUSED(param);
	return AT_BLE_SUCCESS;
}

/* Callback registered for AT_BLE_DISCONNECTED event */
static at_ble_status_t ble_disconnected_cb (void *param)
{
	printf("\nAssignment 3.2: Application disconnected ");
	ble_advertise();
	ALL_UNUSED(param);return AT_BLE_SUCCESS;
}

static at_ble_status_t app_htpt_cfg_indntf_ind_handler(void *params)
{
	at_ble_htpt_cfg_indntf_ind_t htpt_cfg_indntf_ind_params;
	memcpy((uint8_t *)&htpt_cfg_indntf_ind_params, params,
	sizeof(at_ble_htpt_cfg_indntf_ind_t));
	if (htpt_cfg_indntf_ind_params.ntf_ind_cfg == 0x03) {
		printf("Started HTP Temperature Notification");
		Temp_Notification_Flag = true;
	}
	else {
		printf("HTP Temperature Notification Stopped");
		Temp_Notification_Flag = false;
	}
	return AT_BLE_SUCCESS;
}

static const ble_event_callback_t app_gap_cb[] = {
	NULL, // AT_BLE_UNDEFINED_EVENT
	NULL, // AT_BLE_SCAN_INFO
	NULL, // AT_BLE_SCAN_REPORT
	NULL, // AT_BLE_ADV_REPORT
	NULL, // AT_BLE_RAND_ADDR_CHANGED
	NULL, // AT_BLE_CONNECTED
	ble_disconnected_cb, // AT_BLE_DISCONNECTED
	NULL, // AT_BLE_CONN_PARAM_UPDATE_DONE
	NULL, // AT_BLE_CONN_PARAM_UPDATE_REQUEST
	ble_paired_cb, // AT_BLE_PAIR_DONE
	NULL, // AT_BLE_PAIR_REQUEST
	NULL, // AT_BLE_SLAVE_SEC_REQUEST
	NULL, // AT_BLE_PAIR_KEY_REQUEST
	NULL, // AT_BLE_ENCRYPTION_REQUEST
	NULL, // AT_BLE_ENCRYPTION_STATUS_CHANGED
	NULL, // AT_BLE_RESOLV_RAND_ADDR_STATUS
	NULL, // AT_BLE_SIGN_COUNTERS_IND
	NULL, // AT_BLE_PEER_ATT_INFO_IND
	NULL // AT_BLE_CON_CHANNEL_MAP_IND
};

static const ble_event_callback_t app_htpt_handle[] = {
	NULL, // AT_BLE_HTPT_CREATE_DB_CFM
	NULL, // AT_BLE_HTPT_ERROR_IND
	NULL, // AT_BLE_HTPT_DISABLE_IND
	NULL, // AT_BLE_HTPT_TEMP_SEND_CFM
	NULL, // AT_BLE_HTPT_MEAS_INTV_CHG_IND
	app_htpt_cfg_indntf_ind_handler, // AT_BLE_HTPT_CFG_INDNTF_IND
	NULL, // AT_BLE_HTPT_ENABLE_RSP
	NULL, // AT_BLE_HTPT_MEAS_INTV_UPD_RSP
	NULL // AT_BLE_HTPT_MEAS_INTV_CHG_REQ
};


/* Register GAP callbacks at BLE manager level*/
static void register_ble_callbacks (void)
{
	/* Register GAP Callbacks */
	printf("\nAssignment 3.2: Register bluetooth events callbacks");
	status = ble_mgr_events_callback_handler(REGISTER_CALL_BACK,\
	BLE_GAP_EVENT_TYPE,app_gap_cb);
	if (status != true) {
		printf("\n##Error when Registering SAMB11 gap callbacks");
	}
	status = ble_mgr_events_callback_handler(REGISTER_CALL_BACK,\
	BLE_GATT_HTPT_EVENT_TYPE,app_htpt_handle);
	if (status != true) {
		printf("\n##Error when Registering SAMB11 htpt callbacks");
	}
}

static void htp_init (void)
{
	printf("\nAssignment 4.1: Init Health temperature service ");
	/* Create htp service in GATT database*/
	status = at_ble_htpt_create_db(
	HTPT_TEMP_TYPE_CHAR_SUP,
	HTP_TYPE_ARMPIT,
	1,
	30,
	1,
	HTPT_AUTH,
	&htpt_conn_handle);
	if (status != AT_BLE_SUCCESS){
		printf("HTP Data Base creation failed");
		while(true);
	}
}

/* Timer callback */
static void timer_callback_handler(void)
{
	/* Stop timer */
	hw_timer_stop();
	/* Set timer Alarm flag */
	Timer_Flag = true;
	/* Restart Timer */
	hw_timer_start(10);
}

/* Sending the temperature value after reading it from IO1 Xplained Pro */
static void htp_temperature_send(void)
{
	at_ble_prf_date_time_t timestamp;
	float temperature;
	/* Read Temperature Value from IO1 Xplained Pro */
	temperature = at30tse_read_temperature();
	#ifdef HTPT_FAHRENHEIT
	temperature = (((temperature * 9.0)/5.0) + 32.0);
	#endif
	/* Read Temperature Value from IO1 Xplained Pro */
	timestamp.day = 1;
	timestamp.hour = 9;
	timestamp.min = 2;
	timestamp.month = 8;
	timestamp.sec = 36;
	timestamp.year = 15;
	/* Read Temperature Value from IO1 Xplained Pro */
	if(at_ble_htpt_temp_send(convert_ieee754_ieee11073_float((float)temperature),
	&timestamp,
	#ifdef HTPT_FAHRENHEIT
	(at_ble_htpt_temp_flags)(HTPT_FLAG_FAHRENHEIT | HTPT_FLAG_TYPE),
	#else
	(at_ble_htpt_temp_flags)(HTPT_FLAG_CELSIUS | HTPT_FLAG_TYPE),
	#endif
	HTP_TYPE_ARMPIT,
	1
	) == AT_BLE_SUCCESS)
	{
		#ifdef HTPT_FAHRENHEIT
		printf("\nTemperature: %d Fahrenheit", (uint16_t)temperature);
		#else
		printf("\nTemperature: %d Deg Celsius", (uint16_t)temperature);
		#endif
	}
}


int main(void)
{
	// To keep the app executing 
	bool app_exec = true;
	app_state = false;
	#ifdef ENABLE_PTS
	uint8_t function_selector;
	#endif
	
	platform_driver_init();
	acquire_sleep_lock();

	// Initialize serial console 
	serial_console_init();

	DBG_LOG("Initializing Phone Alert Status Profile Application");

	// Initialize the button
	gpio_init();
	button_init();
	button_register_callback(button_cb);

	// Initializing the hardware timer 
	hw_timer_init();

	//Registration of timer callback
	hw_timer_register_callback(timer_callback_handler);
// Start timer 
hw_timer_start(1);

	// initialize the ble chip	and Set the device mac address 
	ble_device_init(NULL);

	// Initializing the profile 
	pas_client_init(NULL);
	register_alert_status_read_callback(app_alert_status_read);
	
	register_ringer_setting_read_callback(app_ringer_setting_read);
	
	register_alert_status_notification_callback(app_alert_status_notify);
	
	register_ringer_setting_notification_callback(app_ringer_setting_notify);
	
	ble_mgr_events_callback_handler(REGISTER_CALL_BACK, BLE_GAP_EVENT_TYPE,app_gap_handle);
		at30tse_init();
		// configure the temperature sensor ADC
		at30tse_write_config_register(AT30TSE_CONFIG_RES(AT30TSE_CONFIG_RES_12_bit));
		// read the temperature from the sensor
		htp_temperature_read();

		// Initialize the htp service
		htp_init();
		// Register Bluetooth events Callbacks
		register_ble_callbacks();
		ble_advertise();
	// Starting the advertisement 
	//pas_client_adv();
	
	
	//ble_advertise();
	// Capturing the events  
	while(app_exec) {
	//	ble_event_task(655);
		if (Timer_Flag & Temp_Notification_Flag)
		{
			htp_temperature_send();
		}
		// BLE Event Task 
		ble_event_task(BLE_EVENT_TIMEOUT);
		if (flag) {
			flag = false;
			#ifdef ENABLE_PTS
			DBG_LOG_PTS("To choose the functionality enter the index of the functionality displayed");
			DBG_LOG_PTS("\t 1.Set Device to Silent");
			DBG_LOG_PTS("\t 2.Set Device to Mute Once");
			DBG_LOG_PTS("\t 3.Set Device to Cancel Mute");
			DBG_LOG_PTS("\t 4.Read Alert Status");
			DBG_LOG_PTS("\t 5.Read Ringer Setting");
			DBG_LOG_PTS("\t 6.Start Service Discovery");
			function_selector = getchar_b11();
			function_selector = function_selector - 48;
			DBG_LOG("The option chosen is %d",function_selector);
			switch(function_selector) {
				
				case DEVICE_SILENT:
				pas_client_write_ringer_control_point(DEVICE_SILENT);
				break;
				
				case DEVICE_MUTE:
				pas_client_write_ringer_control_point(DEVICE_MUTE);
				break;
				
				case DEVICE_NORMAL:
				pas_client_write_ringer_control_point(DEVICE_NORMAL);
				break;
				
				case READ_ALERT_STATUS:
				DBG_LOG("reading the alert status ");
				if (pas_client_read_alert_status_char() != AT_BLE_SUCCESS) {
					DBG_LOG("reading alert status invocation failed");
				}
				
				break;
				
				case READ_RINGER_SETTING:
				DBG_LOG("reading the ringer setting ");
				if (pas_client_read_ringer_setting_char() != AT_BLE_SUCCESS) {
					DBG_LOG("reading ringer control point invocation failed");
				}
				case DISCOVER_ATTRIBUTES:
				DBG_LOG("Starting Service discovery");
				if (pas_client_start_service_discovery() == AT_BLE_SUCCESS) {
					DBG_LOG("Started the service discovery successfully");
					} else {
					DBG_LOG("Service discovery failed");
				}
				break;
				
				default:
				DBG_LOG("Invalid Number pressed %d",function_selector);
			}
			
			#else
			if (press_count == DEVICE_SILENT) {
				DBG_LOG("\r\nDevice to silent");
			}
			else if (press_count == DEVICE_MUTE) {
				DBG_LOG("\r\nDevice to Mute Once");
			}
			else if (press_count == DEVICE_NORMAL) {
				DBG_LOG("\r\nDevice to cancel mute");
			}
			else if (press_count == READ_REQUEST) {
				DBG_LOG("\r\nreading the alert status and ringer setting");
				if ((pas_client_read_ringer_setting_char()) != AT_BLE_SUCCESS) {
					DBG_LOG("reading ringer control point invocation failed");
				}
				
				if ((pas_client_read_alert_status_char()) != AT_BLE_SUCCESS) {
					DBG_LOG("reading alert status invocation failed");
				}

				press_count = DEVICE_SILENT;
				continue;
			}

			pas_client_write_ringer_control_point(press_count);
			press_count++;
			#endif
		}
		
	}

	return 0;
}
/*int main (void)//just temp
{
	platform_driver_init();
	acquire_sleep_lock();
	// Initialize serial console 
	serial_console_init();
	// Hardware timer 
	hw_timer_init();
	// Register the callback 
	hw_timer_register_callback(timer_callback_handler);
	// Start timer 
	hw_timer_start(1);
	printf("\n\rSAMB11 BLE Application");
	// initialize the BLE chip and Set the Device Address 
	ble_device_init(NULL);
	// Initialize the temperature sensor 
	at30tse_init();
	// configure the temperature sensor ADC 
	at30tse_write_config_register(AT30TSE_CONFIG_RES(AT30TSE_CONFIG_RES_12_bit));
	// read the temperature from the sensor 
	htp_temperature_read();
	
	// Initialize the htp service 
	htp_init();
	//Register Bluetooth events Callbacks 
	register_ble_callbacks();
	
	// Start Advertising process 
	ble_advertise();
	while(true) {
		ble_event_task(655);
		if (Timer_Flag & Temp_Notification_Flag)
		{
			htp_temperature_send();
		}
	}
}*/
/*int main(void)//just alert
{
	// To keep the app executing 
	bool app_exec = true;
	app_state = false;
	#ifdef ENABLE_PTS
	uint8_t function_selector;
	#endif
	
	platform_driver_init();
	acquire_sleep_lock();

	// Initialize serial console 
	serial_console_init();

	DBG_LOG("Initializing Phone Alert Status Profile Application");

	// Initialize the button
	gpio_init();
	button_init();
	button_register_callback(button_cb);
	
	// Initializing the hardware timer 
	hw_timer_init();

	//Registration of timer callback
	hw_timer_register_callback(timer_callback_handler);

	// initialize the ble chip	and Set the device mac address 
	ble_device_init(NULL);

	// Initializing the profile 
	pas_client_init(NULL);
	
	// Starting the advertisement 
	pas_client_adv();
	
	register_alert_status_read_callback(app_alert_status_read);
	
	register_ringer_setting_read_callback(app_ringer_setting_read);
	
	register_alert_status_notification_callback(app_alert_status_notify);
	
	register_ringer_setting_notification_callback(app_ringer_setting_notify);
	
	ble_mgr_events_callback_handler(REGISTER_CALL_BACK, BLE_GAP_EVENT_TYPE,app_gap_handle);
	
	// Capturing the events  
	while(app_exec) {
		//BLE Event Task 
		ble_event_task(BLE_EVENT_TIMEOUT);
		if (flag) {
			flag = false;
			#ifdef ENABLE_PTS
			DBG_LOG_PTS("To choose the functionality enter the index of the functionality displayed");
			DBG_LOG_PTS("\t 1.Set Device to Silent");
			DBG_LOG_PTS("\t 2.Set Device to Mute Once");
			DBG_LOG_PTS("\t 3.Set Device to Cancel Mute");
			DBG_LOG_PTS("\t 4.Read Alert Status");
			DBG_LOG_PTS("\t 5.Read Ringer Setting");
			DBG_LOG_PTS("\t 6.Start Service Discovery");
			function_selector = getchar_b11();
			function_selector = function_selector - 48;
			DBG_LOG("The option chosen is %d",function_selector);
			switch(function_selector) {
				
				case DEVICE_SILENT:
				pas_client_write_ringer_control_point(DEVICE_SILENT);
				break;
				
				case DEVICE_MUTE:
				pas_client_write_ringer_control_point(DEVICE_MUTE);
				break;
				
				case DEVICE_NORMAL:
				pas_client_write_ringer_control_point(DEVICE_NORMAL);
				break;
				
				case READ_ALERT_STATUS:
				DBG_LOG("reading the alert status ");
				if (pas_client_read_alert_status_char() != AT_BLE_SUCCESS) {
					DBG_LOG("reading alert status invocation failed");
				}
				
				break;
				
				case READ_RINGER_SETTING:
				DBG_LOG("reading the ringer setting ");
				if (pas_client_read_ringer_setting_char() != AT_BLE_SUCCESS) {
					DBG_LOG("reading ringer control point invocation failed");
				}
				case DISCOVER_ATTRIBUTES:
				DBG_LOG("Starting Service discovery");
				if (pas_client_start_service_discovery() == AT_BLE_SUCCESS) {
					DBG_LOG("Started the service discovery successfully");
					} else {
					DBG_LOG("Service discovery failed");
				}
				break;
				
				default:
				DBG_LOG("Invalid Number pressed %d",function_selector);
			}
			
			#else
			if (press_count == DEVICE_SILENT) {
				DBG_LOG("\r\nDevice to silent");
			}
			else if (press_count == DEVICE_MUTE) {
				DBG_LOG("\r\nDevice to Mute Once");
			}
			else if (press_count == DEVICE_NORMAL) {
				DBG_LOG("\r\nDevice to cancel mute");
			}
			else if (press_count == READ_REQUEST) {
				DBG_LOG("\r\nreading the alert status and ringer setting");
				if ((pas_client_read_ringer_setting_char()) != AT_BLE_SUCCESS) {
					DBG_LOG("reading ringer control point invocation failed");
				}
				
				if ((pas_client_read_alert_status_char()) != AT_BLE_SUCCESS) {
					DBG_LOG("reading alert status invocation failed");
				}

				press_count = DEVICE_SILENT;
				continue;
			}

			pas_client_write_ringer_control_point(press_count);
			press_count++;
			#endif
		}
	}

	return 0;
}*/