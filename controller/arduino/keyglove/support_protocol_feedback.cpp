// Keyglove controller source code - KGAPI "feedback" protocol command parser implementation
// 2014-12-07 by Jeff Rowberg <jeff@rowberg.net>

/*
================================================================================
Keyglove source code is placed under the MIT license
Copyright (c) 2014 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

================================================================================
*/

/**
 * @file support_protocol_feedback.cpp
 * @brief KGAPI "feedback" protocol command parser implementation
 * @author Jeff Rowberg
 * @date 2014-12-07
 *
 * This file implements subsystem-specific command processing functions for the
 * "feedback" part of the KGAPI protocol.
 *
 * This file is autogenerated. Normally it is not necessary to edit this file.
 */

#include "keyglove.h"
#include "support_protocol.h"
//#include "support_protocol_feedback.h"

/**
 * @brief Command processing routine for "feedback" packet class
 * @param[in] rxPacket Incoming KGAPI packet buffer
 * @return Protocol error, if any (0 for success)
 * @see protocol_parse()
 * @see KGAPI command: kg_cmd_feedback_get_blink_mode()
 * @see KGAPI command: kg_cmd_feedback_set_blink_mode()
 * @see KGAPI command: kg_cmd_feedback_get_piezo_mode()
 * @see KGAPI command: kg_cmd_feedback_set_piezo_mode()
 * @see KGAPI command: kg_cmd_feedback_get_vibrate_mode()
 * @see KGAPI command: kg_cmd_feedback_set_vibrate_mode()
 * @see KGAPI command: kg_cmd_feedback_get_rgb_mode()
 * @see KGAPI command: kg_cmd_feedback_set_rgb_mode()
 */
uint8_t process_protocol_command_feedback(uint8_t *rxPacket) {
    // check for valid command IDs
    uint8_t protocol_error = 0;
    switch (rxPacket[3]) {
        #if KG_FEEDBACK & KG_FEEDBACK_BLINK
        case KG_PACKET_ID_CMD_FEEDBACK_GET_BLINK_MODE: // 0x01
            // feedback_get_blink_mode()(uint8_t mode)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t mode;
                uint16_t result = kg_cmd_feedback_get_blink_mode(&mode);
        
                // build response
                uint8_t payload[1] = { mode };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 1, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_BLINK
        
        #if KG_FEEDBACK & KG_FEEDBACK_BLINK
        case KG_PACKET_ID_CMD_FEEDBACK_SET_BLINK_MODE: // 0x02
            // feedback_set_blink_mode(uint8_t mode)(uint16_t result)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_feedback_set_blink_mode(rxPacket[4]);
        
                // build response
                uint8_t payload[2] = { result & 0xFF, (result >> 8) & 0xFF };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_BLINK
        
        #if KG_FEEDBACK & KG_FEEDBACK_PIEZO
        case KG_PACKET_ID_CMD_FEEDBACK_GET_PIEZO_MODE: // 0x03
            // feedback_get_piezo_mode(uint8_t index)(uint8_t mode, uint8_t duration, uint16_t frequency)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t mode;
                uint8_t duration;
                uint16_t frequency;
                uint16_t result = kg_cmd_feedback_get_piezo_mode(rxPacket[4], &mode, &duration, &frequency);
        
                // build response
                uint8_t payload[4] = { mode, duration, frequency & 0xFF, (frequency >> 8) & 0xFF };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 4, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_PIEZO
        
        #if KG_FEEDBACK & KG_FEEDBACK_PIEZO
        case KG_PACKET_ID_CMD_FEEDBACK_SET_PIEZO_MODE: // 0x04
            // feedback_set_piezo_mode(uint8_t index, uint8_t mode, uint8_t duration, uint16_t frequency)(uint16_t result)
            // parameters = 5 bytes
            if (rxPacket[1] != 5) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_feedback_set_piezo_mode(rxPacket[4], rxPacket[5], rxPacket[6], rxPacket[7] | (rxPacket[8] << 8));
        
                // build response
                uint8_t payload[2] = { result & 0xFF, (result >> 8) & 0xFF };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_PIEZO
        
        #if KG_FEEDBACK & KG_FEEDBACK_VIBRATE
        case KG_PACKET_ID_CMD_FEEDBACK_GET_VIBRATE_MODE: // 0x05
            // feedback_get_vibrate_mode(uint8_t index)(uint8_t mode, uint8_t duration)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t mode;
                uint8_t duration;
                uint16_t result = kg_cmd_feedback_get_vibrate_mode(rxPacket[4], &mode, &duration);
        
                // build response
                uint8_t payload[2] = { mode, duration };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_VIBRATE
        
        #if KG_FEEDBACK & KG_FEEDBACK_VIBRATE
        case KG_PACKET_ID_CMD_FEEDBACK_SET_VIBRATE_MODE: // 0x06
            // feedback_set_vibrate_mode(uint8_t index, uint8_t mode, uint8_t duration)(uint16_t result)
            // parameters = 3 bytes
            if (rxPacket[1] != 3) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_feedback_set_vibrate_mode(rxPacket[4], rxPacket[5], rxPacket[6]);
        
                // build response
                uint8_t payload[2] = { result & 0xFF, (result >> 8) & 0xFF };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_VIBRATE
        
        #if KG_FEEDBACK & KG_FEEDBACK_RGB
        case KG_PACKET_ID_CMD_FEEDBACK_GET_RGB_MODE: // 0x07
            // feedback_get_rgb_mode(uint8_t index)(uint8_t mode_red, uint8_t mode_green, uint8_t mode_blue)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t mode_red;
                uint8_t mode_green;
                uint8_t mode_blue;
                uint16_t result = kg_cmd_feedback_get_rgb_mode(rxPacket[4], &mode_red, &mode_green, &mode_blue);
        
                // build response
                uint8_t payload[3] = { mode_red, mode_green, mode_blue };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 3, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_RGB
        
        #if KG_FEEDBACK & KG_FEEDBACK_RGB
        case KG_PACKET_ID_CMD_FEEDBACK_SET_RGB_MODE: // 0x08
            // feedback_set_rgb_mode(uint8_t index, uint8_t mode_red, uint8_t mode_green, uint8_t mode_blue)(uint16_t result)
            // parameters = 4 bytes
            if (rxPacket[1] != 4) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_feedback_set_rgb_mode(rxPacket[4], rxPacket[5], rxPacket[6], rxPacket[7]);
        
                // build response
                uint8_t payload[2] = { result & 0xFF, (result >> 8) & 0xFF };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_RGB
        
        default:
            protocol_error = KG_PROTOCOL_ERROR_INVALID_COMMAND;
    }
    return protocol_error;
}

#if KG_FEEDBACK & KG_FEEDBACK_BLINK
/* 0x01 */ uint8_t (*kg_evt_feedback_blink_mode)(uint8_t mode);
#endif // KG_FEEDBACK & KG_FEEDBACK_BLINK
#if KG_FEEDBACK & KG_FEEDBACK_PIEZO
/* 0x02 */ uint8_t (*kg_evt_feedback_piezo_mode)(uint8_t index, uint8_t mode, uint8_t duration, uint16_t frequency);
#endif // KG_FEEDBACK & KG_FEEDBACK_PIEZO
#if KG_FEEDBACK & KG_FEEDBACK_VIBRATE
/* 0x03 */ uint8_t (*kg_evt_feedback_vibrate_mode)(uint8_t index, uint8_t mode, uint8_t duration);
#endif // KG_FEEDBACK & KG_FEEDBACK_VIBRATE
#if KG_FEEDBACK & KG_FEEDBACK_RGB
/* 0x04 */ uint8_t (*kg_evt_feedback_rgb_mode)(uint8_t index, uint8_t mode_red, uint8_t mode_green, uint8_t mode_blue);
#endif // KG_FEEDBACK & KG_FEEDBACK_RGB
