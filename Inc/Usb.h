/*
 * Usb.h
 * Author: Harsh Anne
 */

#ifndef INC_USB_H
#define INC_USB_H

/* == Headers ============================================================= */

#include "stm32f1xx.h"


/* == Macros ============================================================== */

#define ISTR_MASK (USB_ISTR_CTR_Msk | USB_ISTR_RESET_Msk | USB_ISTR_SUSP_Msk | USB_ISTR_WKUP_Msk)


/* == Types =============================================================== */

/* == Functions =========================================================== */

extern void Usb_Init(
    void
);

extern void Usb_Buffer2PMA(
    uint8_t endpoint
);

extern void Usb_PMA2Buffer(
    uint8_t endpoint
);

extern void Usb_Deinit(
    void
);

extern void USB_LP_CAN1_RX0_IRQHandler(
    void
);


/* == Variables =========================================================== */



#endif /* INC_USB_H */