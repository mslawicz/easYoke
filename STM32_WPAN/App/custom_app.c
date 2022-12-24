/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/custom_app.c
  * @author  MCD Application Team
  * @brief   Custom Example Application (Server)
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_common.h"
#include "dbg_trace.h"
#include "ble.h"
#include "custom_app.h"
#include "custom_stm.h"
#include "stm32_seq.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  /* BatteryService */
  uint8_t               Batlvl_Notification_Status;
  /* DeviceInformationService */
  /* USER CODE BEGIN CUSTOM_APP_Context_t */

  /* USER CODE END CUSTOM_APP_Context_t */

  uint16_t              ConnectionHandle;
} Custom_App_Context_t;

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private defines ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/**
 * START of Section BLE_APP_CONTEXT
 */

static Custom_App_Context_t Custom_App_Context;

/**
 * END of Section BLE_APP_CONTEXT
 */

uint8_t UpdateCharData[247];
uint8_t NotifyCharData[247];

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* BatteryService */
static void Custom_Batlvl_Update_Char(void);
static void Custom_Batlvl_Send_Notification(void);
/* DeviceInformationService */

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void Custom_STM_App_Notification(Custom_STM_App_Notification_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_1 */

  /* USER CODE END CUSTOM_STM_App_Notification_1 */
  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* USER CODE END CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* BatteryService */
    case CUSTOM_STM_BATLVL_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_BATLVL_READ_EVT */

      /* USER CODE END CUSTOM_STM_BATLVL_READ_EVT */
      break;

    case CUSTOM_STM_BATLVL_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_BATLVL_NOTIFY_ENABLED_EVT */

      /* USER CODE END CUSTOM_STM_BATLVL_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_BATLVL_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_BATLVL_NOTIFY_DISABLED_EVT */

      /* USER CODE END CUSTOM_STM_BATLVL_NOTIFY_DISABLED_EVT */
      break;

    /* DeviceInformationService */
    case CUSTOM_STM_MANUFNAME_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_MANUFNAME_READ_EVT */

      /* USER CODE END CUSTOM_STM_MANUFNAME_READ_EVT */
      break;

    case CUSTOM_STM_MODNUMB_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_MODNUMB_READ_EVT */

      /* USER CODE END CUSTOM_STM_MODNUMB_READ_EVT */
      break;

    case CUSTOM_STM_PNPID_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_PNPID_READ_EVT */

      /* USER CODE END CUSTOM_STM_PNPID_READ_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_STM_App_Notification_default */

      /* USER CODE END CUSTOM_STM_App_Notification_default */
      break;
  }
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_2 */

  /* USER CODE END CUSTOM_STM_App_Notification_2 */
  return;
}

void Custom_APP_Notification(Custom_App_ConnHandle_Not_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_APP_Notification_1 */

  /* USER CODE END CUSTOM_APP_Notification_1 */

  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_APP_Notification_Custom_Evt_Opcode */

    /* USER CODE END P2PS_CUSTOM_Notification_Custom_Evt_Opcode */
    case CUSTOM_CONN_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_CONN_HANDLE_EVT */

      /* USER CODE END CUSTOM_CONN_HANDLE_EVT */
      break;

    case CUSTOM_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_DISCON_HANDLE_EVT */

      /* USER CODE END CUSTOM_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_APP_Notification_default */

      /* USER CODE END CUSTOM_APP_Notification_default */
      break;
  }

  /* USER CODE BEGIN CUSTOM_APP_Notification_2 */

  /* USER CODE END CUSTOM_APP_Notification_2 */

  return;
}

void Custom_APP_Init(void)
{
  /* USER CODE BEGIN CUSTOM_APP_Init */
    const uint8_t bleDisPnpId[] =
    {
            VENDOR_ID_SOURCE,
            VENDOR_ID & 0xFF,
            (VENDOR_ID >> 8) & 0xFF,
            PRODUCT_ID & 0xFF,
            (PRODUCT_ID >> 8) & 0xFF,
            PRODUCT_VERSION & 0xFF,
            (PRODUCT_VERSION >> 8) & 0xFF
    };
    Custom_STM_App_Update_Char(CUSTOM_STM_MANUFNAME, (uint8_t*)MANUFACTURER_NAME);
    Custom_STM_App_Update_Char(CUSTOM_STM_MODNUMB, (uint8_t*)MODEL_NUMBER);
    Custom_STM_App_Update_Char(CUSTOM_STM_PNPID, (uint8_t*)&bleDisPnpId);
  /* USER CODE END CUSTOM_APP_Init */
  return;
}

/* USER CODE BEGIN FD */
void updateBatteryLevel(uint8_t value)
{
    UpdateCharData[0] = value;
    Custom_Batlvl_Update_Char();
}

void notifyBatteryLevel(uint8_t value)
{
    NotifyCharData[0] = value;
    Custom_Batlvl_Send_Notification();
}
/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/

/* BatteryService */
void Custom_Batlvl_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Batlvl_UC_1*/
updateflag = 1;
  /* USER CODE END Batlvl_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_BATLVL, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Batlvl_UC_Last*/

  /* USER CODE END Batlvl_UC_Last*/
  return;
}

void Custom_Batlvl_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Batlvl_NS_1*/
  updateflag = 1;
  /* USER CODE END Batlvl_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_BATLVL, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Batlvl_NS_Last*/

  /* USER CODE END Batlvl_NS_Last*/

  return;
}

/* DeviceInformationService */

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS*/

/* USER CODE END FD_LOCAL_FUNCTIONS*/
