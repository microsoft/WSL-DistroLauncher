LanguageNames = (English=0x409:MSG00409)

MessageId=1002 SymbolicName=MSG_STATUS_UNINSTALL_PROMPT
Language=English
This will remove this distro from the filesystem. The app will remain on your 
PC, but all linux files for this distro will be removed. Are you sure you would 
like to proceed? (This cannot be undone)
.

MessageId=1003 SymbolicName=MSG_STATUS_UNINSTALLING
Language=English
Uninstalling...
.

MessageId=1004 SymbolicName=MSG_USAGE
Language=English
Launches or configures a linux distribution.

Usage: 
    <no args> 
      - Launches the distro's default behavior. By default, this launches your default shell.
    
    run <command line> 
      - Run the given command line in that distro, using the default configuration.
      - Everything after `run ` is passed to the linux LaunchProcess call.

    config [setting [value]] 
      - Configure certain settings for this distro.
      - Settings are any of the following (by default)
        - `--default-user <username>`: Set the default user for this distro to <username>

    clean
      - Uninstalls the distro. The appx remains on your machine. This can be 
        useful for "factory resetting" your instance. This removes the linux 
        filesystem from the disk, but not the app from your PC, so you don't 
        need to redownload the entire tar.gz again.
    
    help 
      - Print this usage message.
.

MessageId=1005 SymbolicName=MSG_STATUS_INSTALLING
Language=English
Installing, this may take a few minutes...
.

MessageId=1006 SymbolicName=MSG_INSTALL_FAILURE
Language=English
Installation Failed!
.

MessageId=1007 SymbolicName=MSG_INSTALL_SUCCESS
Language=English
Installation successful!
.

MessageId=1008 SymbolicName=MSG_AGREE_PROMPT
Language=English
Type "%1" to continue: %0
.

MessageId=1009 SymbolicName=MSG_AGREE_PROMPT_WORD
Language=English
y%0
.

MessageId=1010 SymbolicName=MSG_AGREE_REJECTED
Language=English
Accepting is required to proceed. Exiting...
.

MessageId=1011 SymbolicName=MSG_ERROR_CODE
Language=English
Error: 0x%1!x!
.

MessageId=1012 SymbolicName=MSG_UNINSTALL_WORKING
Language=English
Removing filesystem...
.

MessageId=1013 SymbolicName=MSG_UNINSTALL_SUCCESS
Language=English
Successfully removed distro.
.

MessageId=1014 SymbolicName=MSG_ENTER_USERNAME
Language=English
Enter new UNIX username: %0
.

MessageId=1015 SymbolicName=MSG_FOUND_USER
Language=English
Found UNIX user: %1
.

MessageId=1016 SymbolicName=MSG_CREATE_USER_SUCCESS
Language=English
Default UNIX user set to: %1
.

MessageId=1017 SymbolicName=MSG_INVALID_USER_NAME
Language=English
Invalid user name.
.

MessageId=1018 SymbolicName=MSG_UNINSTALL_FAILED
Language=English
Failed to clean this distro installation.
.

MessageId=1019 SymbolicName=MSG_CREATE_USER_PROMPT
Language=English
Please create a default UNIX user account. The username does not need to match your Windows username.
For more information visit: https://aka.ms/wslusers
.

MessageId=1020 SymbolicName=MSG_INVALID_ARGS
Language=English
Invalid command line arg '%1'
.

MessageId=1021 SymbolicName=MSG_PRESS_A_KEY
Language=English
Press any key to continue...
.

MessageId=1022 SymbolicName=MSG_INVALID_COMMANDLINE
Language=English
Could not parse commandline. Use `help` to see usage.
.

MessageId=1023 SymbolicName=MSG_SET_USER_FAILURE
Language=English
Failed to set default user to: %1
.

MessageId=1024 SymbolicName=MSG_MISSING_OPTIONAL_COMPONENT
Language=English
The WSL optional component is not enabled. Please enable it and try again.
See https://aka.ms/wslinstall for details.
.

MessageId=1025 SymbolicName=INSTALL_ALREADY_EXISTS
Language=English
It appears this distro's installation has become corrupted.
Please try uninstalling and reinstalling the app.
.
