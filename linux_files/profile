# /etc/profile: system-wide .profile file for the Bourne shell (sh(1))
# and Bourne compatible shells (bash(1), ksh(1), ash(1), ...).

IS_WSL=`grep -i microsoft /proc/version`
if test "$IS_WSL" = ""; then
  if [ "`id -u`" -eq 0 ]; then
    PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
  else
    PATH="/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games"
  fi
fi
export PATH

if [ "${PS1-}" ]; then
  if [ "${BASH-}" ] && [ "$BASH" != "/bin/sh" ]; then
    # The file bash.bashrc already sets the default PS1.
    # PS1='\h:\w\$ '
    if [ -f /etc/bash.bashrc ]; then
      . /etc/bash.bashrc
    fi
  else
    if [ "`id -u`" -eq 0 ]; then
      PS1='# '
    else
      PS1='$ '
    fi
  fi
fi

if [ -d /etc/profile.d ]; then
  for i in /etc/profile.d/*.sh; do
    if [ -r $i ]; then
      . $i
    fi
  done
  unset i
fi

# enable external x display
export DISPLAY=:0

# enable external libgl 
export LIBGL_ALWAYS_INDIRECT=1

# speed up some GUI apps like gedit
export NO_AT_BRIDGE=1

# alias wlinux helper apps
alias wlinux-setup='bash /etc/setup'
alias wlinux-help='bash /etc/helpme'

# does .firstrun exist? if not, mention wlinux-setup and touch .firstrun
if [ ! -f ~/.firstrun ]; then
    echo "Welcome to WLinux. Type 'wlinux-setup' to run the setup tool. You will only see this message once."
    touch ~/.firstrun
fi
