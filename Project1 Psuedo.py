# Pseudocode for Encrypt and Decrypt Program

# Function to shift a character by a specified amount
function shiftChar(character, shift_amount):
    if character is a lowercase letter:
        result = (character + shift_amount) % 26
        while result < 'a':
            result += 26
        return result
    return character

# Function to determine the shift amount based on the number of vowels in a key
function getMethod2ShiftAmount(key):
    vowels = 0
    for each character in key:
        if character is a vowel:
            increment vowels
    return (vowels + length of key) % 26

# Function to determine the shift amount based on the number of overlapping characters in two keys
function getMethod3ShiftAmount(key1, key2):
    count = 0
    for each character in key1:
        for each character in key2:
            if characters are the same:
                increment count
    return count % 26

# Function to encrypt a character based on a specified method and keys
function encryptChar(character, method, key1, key2):
    switch method:
        case 1:
            character = shiftChar(character, 1)
        case 2:
            shift_amount = getMethod2ShiftAmount(key1)
            character = shiftChar(character, shift_amount)
        case 3:
            shift_amount = getMethod3ShiftAmount(key1, key2)
            character = shiftChar(character, shift_amount)
        default:
            display "Invalid encryption method"
    return character

# Function to decrypt a character based on a specified method and keys
function decryptChar(character, method_choice, key1, key2):
    switch method_choice:
        case 1:
            character = shiftChar(character, -1)
        case 2:
            shift_amount = -getMethod2ShiftAmount(key1)
            character = shiftChar(character, shift_amount)
        case 3:
            shift_amount = -getMethod3ShiftAmount(key1, key2)
            character = shiftChar(character, shift_amount)
        default:
            display "Invalid decryption method"
    return character

# Function to encrypt a message based on a specified method and keys
function encryptMessage(message, method_choice, key1, key2):
    for each character in message:
        character = encryptChar(character, method_choice, key1, key2)
    return message

# Function to decrypt a message based on a specified method and keys
function decryptMessage(message, method_choice, key1, key2):
    for each character in message:
        character = decryptChar(character, method_choice, key1, key2)
    return message

# Main program
function main():
    option = 0
    method = 0
    key1 = ""
    key2 = ""
    message = ""
    setkey1 = false
    setkey2 = false
    setmethod = false
    wrongoption = false

    repeat until option is 6:
        if not wrongoption:
            display "Please input 1-6 followed by enter to navigate the menu:"
            display "1. Set Encryption Key 1"
            display "2. Set Encryption Key 2"
            display "3. Select Encryption Method"
            display "4. Encrypt Message"
            display "5. Decrypt Message"
            display "6. Exit Program"
            input option
        else:
            wrongoption = false

        switch option:
            case 1:
                display "Enter key:"
                input key1
                while length of key1 < 1:
                    display "Invalid key"
                    display "Enter key:"
                    input key1
                display "Successfully set encryption key1 to " + key1
                setkey1 = true
            case 2:
                display "Enter key:"
                input key2
                while length of key2 < 1:
                    display "Invalid key"
                    display "Enter key:"
                    input key2
                display "Successfully set encryption key2 to " + key2
                setkey2 = true
            case 3:
                display "Please input 1-4 to decide encryption technique:"
                display "1. Method1 only (shift by 1)"
                display "2. Method2 only (shift by first key)"
                display "3. Method3 only (shift by both keys)"
                display "4. Mix of Method1, Method2, Method3"
                input method
                while true:
                    if not (method is between 1 and 4):
                        display "Invalid encryption choice"
                        clear input buffer
                        input method
                    else:
                        setmethod = true
                        display "Successfully set encryption type to " + method
                        exit loop
            case 4:
                if not (setkey1 and setkey2 and setmethod):
                    display "You cannot do this until you set both keys and choose an encryption method"
                else:
                    display "Enter your message to encrypt:"
                    input message
                    result = encryptMessage(message, method, key1, key2)
                    display result
            case 5:
                if not (setkey1 and setkey2 and setmethod):
                    display "You cannot do this until you set both keys and choose an encryption method"
                else:
                    display "Enter your message to decrypt:"
                    input message
                    result = decryptMessage(message, method, key1, key2)
                    display result
            case 6:
                exit loop

    display "Goodbye"

# Start the program
call main()
