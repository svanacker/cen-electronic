#ifndef BUTTON_BOARD_ARM_2020_H
#define BUTTON_BOARD_ARM_2020_H

#include "../../../drivers/ioExpander/ioExpander.h"

// First Button
#define MASK_MENU_BUTTON_ARM_0                           0x01
#define MASK_MENU_BUTTON_FLAG_1                          0x02
#define MASK_MENU_BUTTON_HOOK_REEF_2                     0x04
#define MASK_MENU_BUTTON_HOOK_FLOOR_3                    0x08
#define MASK_MENU_BUTTON_HOOK_COMPLEX_4                  0x10

// Second Button

// -> ARM
#define MASK_MENU_ITEM_BUTTON_ARM_LEFT                   0x20
#define MASK_MENU_ITEM_BUTTON_ARM_RIGHT                  0x40
#define MASK_MENU_ITEM_BUTTON_ARM_CENTER                 0x80

// -> FLAG
#define MASK_MENU_ITEM_BUTTON_FLAG_ON                    0x40
#define MASK_MENU_ITEM_BUTTON_FLAG_OFF                   0x80

// -> HOOK FOR REEF
#define MASK_MENU_ITEM_BUTTON_HOOK_REEF_DOWN_ALL         0x10
#define MASK_MENU_ITEM_BUTTON_HOOK_REEF_UP_ALL           0x20
#define MASK_MENU_ITEM_BUTTON_HOOK_TAKE_ALL              0x40
#define MASK_MENU_ITEM_BUTTON_HOOK_RELEASE_ALL           0x80

// -> HOOK FOR FLOOR
#define MASK_MENU_ITEM_BUTTON_HOOK_FLOOR_PREPARE_ALL     0x40
#define MASK_MENU_ITEM_BUTTON_HOOK_FLOOR_LOCK_ALL        0x80

// -> HOOK COMPLEX
#define MASK_MENU_ITEM_BUTTON_HOOK_TAKE_AND_UP_ALL       0x40
#define MASK_MENU_ITEM_BUTTON_HOOK_DOWN_AND_RELEASE_ALL  0x80

/**
 * The event Callback which will be called when ioExpander change.
 * @param ioExpander
 * @param value
 */
void arm2020IoExpanderOnValueChangeEvent(IOExpander* ioExpander, unsigned char value, int* eventContext);

#endif
