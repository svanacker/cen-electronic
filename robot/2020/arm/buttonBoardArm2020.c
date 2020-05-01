#include "buttonBoardArm2020.h"

#include <stdlib.h>

#include "../../../common/io/printWriter.h"
#include "../../../common/log/logger.h"

#include "../../../common/error/error.h"
#include "../../../common/pwm/servo/servoList.h"

#include "arm2020.h"

void arm2020IoExpanderOnValueChangeEvent(IOExpander* ioExpander, unsigned char value, int* eventContext) {
    appendStringAndDecLN(getDebugOutputStreamLogger(), "arm2020IoExpanderOnValueChangeEvent:value=", value);
    ServoList* servoList = (ServoList*) eventContext;
    if (servoList == NULL) {
        writeError(SERVO_LIST_NULL);
        return;
    }
    // ARM
    if (value & MASK_MENU_BUTTON_ARM_0) {
        if (value & MASK_MENU_ITEM_BUTTON_ARM_LEFT) {
            lateralArm2020(servoList, 0x01);
        }
        else if (value & MASK_MENU_ITEM_BUTTON_ARM_RIGHT) {
            lateralArm2020(servoList, 0x02);
        }
        else if (value & MASK_MENU_ITEM_BUTTON_ARM_CENTER) {
            lateralArm2020(servoList, 0x00);
        }
    }
    // FLAG
    else if (value & MASK_MENU_BUTTON_FLAG_1) {
        if (value & MASK_MENU_ITEM_BUTTON_FLAG_ON) {
            arm2020FlagUp(servoList);
        }
        else if (value & MASK_MENU_ITEM_BUTTON_FLAG_ON) {
            arm2020FlagDown(servoList);
        }
    }
    
    // REEF
    else if (value & MASK_MENU_BUTTON_HOOK_REEF_2) {
        if (value & MASK_MENU_ITEM_BUTTON_HOOK_REEF_DOWN_ALL) {
            arm2020HookDownAll(servoList);
        }
        else if (value & MASK_MENU_ITEM_BUTTON_HOOK_REEF_UP_ALL) {
            arm2020HookUpAll(servoList, 0);
        }
        else if (value & MASK_MENU_ITEM_BUTTON_HOOK_TAKE_ALL) {
            arm2020HookTakeAll (servoList);
        }
        else if (value & MASK_MENU_ITEM_BUTTON_HOOK_RELEASE_ALL) {
            arm2020HookReleaseAll(servoList, 0);
        }
    }
    
    // FLOOR
    else if (value & MASK_MENU_BUTTON_HOOK_FLOOR_3) {
        if (value & MASK_MENU_ITEM_BUTTON_HOOK_FLOOR_PREPARE_ALL) {
            arm2020HookPrepareFloorAll(servoList);
        }
        else if (value & MASK_MENU_ITEM_BUTTON_HOOK_FLOOR_LOCK_ALL) {
            arm2020HookLockFloorAll(servoList);
        }
    }

    // COMPLEX
    else if (value & MASK_MENU_BUTTON_HOOK_COMPLEX_4) {
        if (value & MASK_MENU_ITEM_BUTTON_HOOK_TAKE_AND_UP_ALL) {
            arm2020TakeAndUpAll(servoList);
        }
        else if (value & MASK_MENU_ITEM_BUTTON_HOOK_DOWN_AND_RELEASE_ALL) {
            arm2020DownAndReleaseAll(servoList);
        }
    }
}
