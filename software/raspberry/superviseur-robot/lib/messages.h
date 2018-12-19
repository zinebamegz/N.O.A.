/*
 * Copyright (C) 2018 dimercur
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <string>
#include "img.h"

/**
 * Message ID defined for system communication
 * 
 * @brief List of available message ID
 * 
 */
typedef enum {
    //Generic messages
    MESSAGE_EMPTY = 0,
    MESSAGE_LOG,
    
    // Message containing answer (after robot command, or for monitor)
    MESSAGE_ANSWER,
           
    // messages for serial communication with robot
    MESSAGE_OPEN_COM,
    MESSAGE_CLOSE_COM,
         
    // Messages specific to server
    MESSAGE_MONITOR_LOST,
    
    // Messages for camera   
    MESSAGE_CAM_OPEN,
    MESSAGE_CAM_CLOSE,
    MESSAGE_ASK_ARENA,
    MESSAGE_ARENA_CONFIRM,
    MESSAGE_ARENA_INFIRM,
    MESSAGE_COMPUTE_POSITION,
    MESSAGE_STOP_COMPUTE_POSITION,
    MESSAGE_POSITION,
    MESSAGE_IMAGE,
            
    // Messages for robot
    MESSAGE_ROBOT_PING,
    MESSAGE_ROBOT_RESET,
    MESSAGE_ROBOT_START_WITH_WD,
    MESSAGE_ROBOT_START_WITHOUT_WD,
    MESSAGE_ROBOT_RELOAD_WD,
    MESSAGE_ROBOT_MOVE,
    MESSAGE_ROBOT_TURN,
    MESSAGE_ROBOT_GO_FORWARD,
    MESSAGE_ROBOT_GO_BACK,
    MESSAGE_ROBOT_GO_LEFT,
    MESSAGE_ROBOT_GO_RIGHT,
    MESSAGE_ROBOT_STOP,
    MESSAGE_ROBOT_POWEROFF,
    MESSAGE_ROBOT_GET_BATTERY,
    MESSAGE_ROBOT_BATTERY_LEVEL,
    MESSAGE_ROBOT_GET_STATE,
    MESSAGE_ROBOT_CURRENT_STATE
} MessageID;

typedef enum {
    ANSWER_ACK=0,
    ANSWER_NACK,
    ANSWER_LOST_ROBOT,
    ANSWER_ROBOT_TIMEOUT,
    ANSWER_ROBOT_UNKNOWN_COMMAND,
    ANSWER_ROBOT_ERROR,
    ANSWER_ROBOT_CHECKSUM
} AnswerID;

typedef enum {
    BATTERY_UNKNOWN=-1,
    BATTERY_EMPTY=0,
    BATTERY_LOW,
    BATTERY_FULL
} BatteryLevel;

typedef enum {
    ROBOT_NOT_BUSY=0,
    ROBOT_BUSY
} RobotState;

using namespace std;

/**
 * Base class for messaging
 * 
 * @brief Base class for messaging
 * 
 */
class Message {
public:
    /**
     * Create a new, empty message
     */
    Message();

    /**
     * Create a new, empty message
     */
    Message(MessageID id);
    
    /**
     * Destroy message
     */
    virtual ~Message();

    /**
     * Translate content of message into a string that can be displayed
     * @return A string describing message contents
     */
    virtual string ToString();

    /**
     * Allocate a new mesage and copy contents of current message
     * @return A message, copy of current
     */
    virtual Message* Copy();

    /**
     * Get message ID
     * @return Current message ID
     */
    MessageID GetID() {
        return messageID;
    }

    /**
     * Set message ID
     * @param id Message ID
     */
    virtual void SetID(MessageID id);

    /**
     * Comparison operator
     * @param msg Message to be compared
     * @return true if message are equal, false otherwise
     */
    virtual bool operator==(const Message& msg) {
        return (messageID == msg.messageID);
    }

    /**
     * Difference operator
     * @param msg Message to be compared
     * @return true if message are different, false otherwise
     */
    virtual bool operator!=(const Message& msg) {
        return !(messageID == msg.messageID);
    }

protected:
    /**
     * Message identifier (@see MessageID)
     */
    MessageID messageID;

    /**
     * Verify if message ID is compatible with current message type
     * @param id Message ID
     * @return true, if message ID is acceptable, false otherwise
     */
    virtual bool CheckID(MessageID id);
};


/**
 * Message class for holding float value, based on Message class
 * 
 * @brief Float message class
 * 
 */
class MessageInt : public Message {
public:
    /**
     * Create a new, empty float message
     */
    MessageInt();

    /**
     * Create a new float message, with given ID and value
     * @param id Message ID
     * @param val Message value
     * @throw std::runtime_error if message ID is incompatible with float data
     */
    MessageInt(MessageID id, int val);

    /**
     * Set message ID
     * @param id Message ID
     * @throw std::runtime_error if message ID is incompatible with float data
     */
    void SetID(MessageID id);

    /**
     * Get message value (int)
     * @return int value
     */
    int GetValue() {
        return value;
    }

    /**
     * Set message value (int)
     * @param val int value to store in message
     */
    void SetValue(int val) {
        this->value = val;
    }

    /**
     * Translate content of message into a string that can be displayed
     * @return A string describing message contents
     */
    string ToString();

    /**
     * Allocate a new mesage and copy contents of current message
     * @return A message, copy of current
     */
    Message* Copy();

    /**
     * Comparison operator
     * @param msg Message to be compared
     * @return true if message are equal, false otherwise
     */
    virtual bool operator==(const MessageInt& msg) {
        return ((messageID == msg.messageID) && (value == msg.value));
    }

    /**
     * Difference operator
     * @param msg Message to be compared
     * @return true if message are different, false otherwise
     */
    virtual bool operator!=(const MessageInt& msg) {
        return !((messageID == msg.messageID) && (value == msg.value));
    }
    
protected:
    /**
     * Message integer value
     */
    int value;

    /**
     * Verify if message ID is compatible with current message type
     * @param id Message ID
     * @return true, if message ID is acceptable, false otherwise
     */
    bool CheckID(MessageID id);
};

/**
 * Message class for holding string value, based on Message class
 * 
 * @brief String message class
 * 
 */
class MessageString : public Message {
public:
    /**
     * Create a new, empty string message
     */
    MessageString();

    /**
     * Create a new string message, with given ID and string
     * @param id Message ID
     * @param s Message string
     * @throw std::runtime_error if message ID is incompatible with string data
     */
    MessageString(MessageID id, string s);

    /**
     * Set message ID
     * @param id Message ID
     * @throw std::runtime_error if message ID is incompatible with string data
     */
    void SetID(MessageID id);

    /**
     * Get message string
     * @return String
     */
    string GetString() {
        return s;
    }

    /**
     * Set message string
     * @param s String to store in message
     */
    void SetString(string s) {
        this->s = s;
    }

    /**
     * Translate content of message into a string that can be displayed
     * @return A string describing message contents
     */
    string ToString();

    /**
     * Allocate a new message and copy contents of current message
     * @return A message, copy of current
     */
    Message* Copy();

    /**
     * Comparison operator
     * @param msg Message to be compared
     * @return true if message are equal, false otherwise
     */
    virtual bool operator==(const MessageString& msg) {
        return ((messageID == msg.messageID) && (s == msg.s));
    }

    /**
     * Difference operator
     * @param msg Message to be compared
     * @return true if message are different, false otherwise
     */
    virtual bool operator!=(const MessageString& msg) {
        return !((messageID == msg.messageID) && (s == msg.s));
    }
protected:
    /**
     * Message content
     */
    string s;

    /**
     * Verify if message ID is compatible with current message type
     * @param id Message ID
     * @return true, if message ID is acceptable, false otherwise
     */
    bool CheckID(MessageID id);
};

/**
 * Message class for holding image, based on Message class
 * 
 * @brief Image message class
 * 
 */
class MessageImg : public Message {
public:
    /**
     * Create a new, empty image message
     */
    MessageImg();

    /**
     * Create a new image message, with given ID and boolean value
     * @param id Message ID
     * @param image Pointer to image
     * @throw std::runtime_error if message ID is incompatible with image message
     */
    MessageImg(MessageID id, Img* image);

    /**
     * Destroy Image message
     */
    virtual ~MessageImg();
    
    /**
     * Set message ID
     * @param id Message ID
     * @throw std::runtime_error if message ID is incompatible withimage message
     */
    void SetID(MessageID id);

    /**
     * Get message image
     * @return Pointer to image
     */
    Img* GetImage() {
        return image;
    }

    /**
     * Set message image
     * @param image Pointer to image object
     */
    void SetImage(Img* image);

    /**
     * Translate content of message into a string that can be displayed
     * @return A string describing message contents
     */
    string ToString();

    /**
     * Allocate a new message and copy contents of current message
     * @return A message, copy of current
     */
    Message* Copy();

protected:
    /**
     * Message image
     */
    Img* image;

    /**
     * Verify if message ID is compatible with current message type
     * @param id Message ID
     * @return true, if message ID is acceptable, false otherwise
     */
    bool CheckID(MessageID id);
};

/**
 * Message class for holding position, based on Message class
 * 
 * @brief Position message class
 * 
 */
class MessagePosition : public Message {
public:
    /**
     * Create a new, empty image message
     */
    MessagePosition();

    /**
     * Create a new image message, with given ID and boolean value
     * @param id Message ID
     * @param pos Position
     * @throw std::runtime_error if message ID is incompatible with image message
     */
    MessagePosition(MessageID id, Position& pos);

    /**
     * Set message ID
     * @param id Message ID
     * @throw std::runtime_error if message ID is incompatible withimage message
     */
    void SetID(MessageID id);

    /**
     * Get message image
     * @return Pointer to image
     */
    Position GetPosition() {
        return pos;
    }

    /**
     * Set message image
     * @param image Pointer to image object
     */
    void SetPosition(Position& pos);

    /**
     * Translate content of message into a string that can be displayed
     * @return A string describing message contents
     */
    string ToString();

    /**
     * Allocate a new message and copy contents of current message
     * @return A message, copy of current
     */
    Message* Copy();

protected:
    /**
     * Message position
     */
   Position pos;

    /**
     * Verify if message ID is compatible with current message type
     * @param id Message ID
     * @return true, if message ID is acceptable, false otherwise
     */
    bool CheckID(MessageID id);
};

/**
 * Message class for holding battery level, based on Message class
 * 
 * @brief Position message class
 * 
 */
class MessageBattery : public Message {
public:
    /**
     * Create a new, empty image message
     */
    MessageBattery();

    /**
     * Create a new image message, with given ID and boolean value
     * @param id Message ID
     * @param image Pointer to image
     * @throw std::runtime_error if message ID is incompatible with image message
     */
    MessageBattery(MessageID id, BatteryLevel level);

    /**
     * Set message ID
     * @param id Message ID
     * @throw std::runtime_error if message ID is incompatible withimage message
     */
    void SetID(MessageID id);

    /**
     * Get message image
     * @return Pointer to image
     */
    BatteryLevel GetLevel() {
        return level;
    }

    /**
     * Set message image
     * @param image Pointer to image object
     */
    void SetLevel(BatteryLevel level);

    /**
     * Translate content of message into a string that can be displayed
     * @return A string describing message contents
     */
    string ToString();

    /**
     * Allocate a new message and copy contents of current message
     * @return A message, copy of current
     */
    Message* Copy();

protected:
    /**
     * Message position
     */
   BatteryLevel level;

    /**
     * Verify if message ID is compatible with current message type
     * @param id Message ID
     * @return true, if message ID is acceptable, false otherwise
     */
    bool CheckID(MessageID id);
};

/**
 * Message class for holding answer, based on Message class
 * 
 * @brief Answer message class
 * 
 */
class MessageAnswer : public Message {
public:
    /**
     * Create a new, empty image message
     */
    MessageAnswer();

    /**
     * Create a new image message, with given ID and boolean value
     * @param id Message ID
     * @param ans Answer ID
     * @throw std::runtime_error if message ID is incompatible with image message
     */
    MessageAnswer(MessageID id, AnswerID ans);

    /**
     * Set message ID
     * @param id Message ID
     * @throw std::runtime_error if message ID is incompatible withimage message
     */
    void SetID(MessageID id);

    /**
     * Get message image
     * @return Pointer to image
     */
    AnswerID GetAnswer() {
        return answer;
    }

    /**
     * Set message answer
     * @param ans Answer ID
     */
    void SetAnswer(AnswerID ans);

    /**
     * Translate content of message into a string that can be displayed
     * @return A string describing message contents
     */
    string ToString();

    /**
     * Allocate a new message and copy contents of current message
     * @return A message, copy of current
     */
    Message* Copy();

protected:
    /**
     * Message answer
     */
   AnswerID answer;

    /**
     * Verify if message ID is compatible with current message type
     * @param id Message ID
     * @return true, if message ID is acceptable, false otherwise
     */
    bool CheckID(MessageID id);
};

/**
 * Message class for holding robot state, based on Message class
 * 
 * @brief Answer message class
 * 
 */
class MessageState: public Message {
public:
    /**
     * Create a new, empty image message
     */
    MessageState();

    /**
     * Create a new image message, with given ID and boolean value
     * @param id Message ID
     * @param image Pointer to image
     * @throw std::runtime_error if message ID is incompatible with image message
     */
    MessageState(MessageID id, RobotState state);

    /**
     * Set message ID
     * @param id Message ID
     * @throw std::runtime_error if message ID is incompatible withimage message
     */
    void SetID(MessageID id);

    /**
     * Get message image
     * @return Pointer to image
     */
    RobotState GetState() {
        return state;
    }

    /**
     * Set message image
     * @param image Pointer to image object
     */
    void SetState(RobotState state);

    /**
     * Translate content of message into a string that can be displayed
     * @return A string describing message contents
     */
    string ToString();

    /**
     * Allocate a new message and copy contents of current message
     * @return A message, copy of current
     */
    Message* Copy();

protected:
    /**
     * Robot state
     */
   RobotState state;

    /**
     * Verify if message ID is compatible with current message type
     * @param id Message ID
     * @return true, if message ID is acceptable, false otherwise
     */
    bool CheckID(MessageID id);
};
#endif /* __MESSAGES_H__ */
