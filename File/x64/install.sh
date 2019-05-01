#!/bin/bash
contains_element() { #{{{
  #check if an element exist in a string
  for e in "${@:2}"; do [[ $e == $1 ]] && break; done;
} #}}}
print_line() { #{{{
  printf "%$(tput cols)s\n"|tr ' ' '-'
} #}}}
pause_function() { #{{{
  print_line
  if [[ $AUTOMATIC_MODE -eq 0 ]]; then
    read -e -sn 1 -p "Press enter to continue..."
  fi
} #}}}
invalid_option() { #{{{
  print_line
  echo "Invalid option. Try another one."
  pause_function
} #}}}
configure_mirrorlist(){
  echo "Add Arch Linux CN Repository..."
  echo -e "[archlinuxcn]\nSigLevel = Optional TrustedOnly\nServer = http://mirrors.163.com/archlinux-cn/\$arch" >> /etc/pacman.conf
  echo "Configure mirrorlist..."
  local countries_code=("AU" "AT" "BY" "BE" "BR" "BG" "CA" "CL" "CN" "CO" "CZ" "DK" "EE" "FI" "FR" "DE" "GR" "HU" "IN" "IE" "IL" "IT" "JP" "KZ" "KR" "LV" "LU" "MK" "NL" "NC" "NZ" "NO" "PL" "PT" "RO" "RU" "RS" "SG" "SK" "ZA" "ES" "LK" "SE" "CH" "TW" "TR" "UA" "GB" "US" "UZ" "VN")
  local countries_name=("Australia" "Austria" "Belarus" "Belgium" "Brazil" "Bulgaria" "Canada" "Chile" "China" "Colombia" "Czech Republic" "Denmark" "Estonia" "Finland" "France" "Germany" "Greece" "Hungary" "India" "Ireland" "Israel" "Italy" "Japan" "Kazakhstan" "Korea" "Latvia" "Luxembourg" "Macedonia" "Netherlands" "New Caledonia" "New Zealand" "Norway" "Poland" "Portugal" "Romania" "Russian" "Serbia" "Singapore" "Slovakia" "South Africa" "Spain" "Sri Lanka" "Sweden" "Switzerland" "Taiwan" "Turkey" "Ukraine" "United Kingdom" "United States" "Uzbekistan" "Viet Nam")
  country_list(){
    echo "Select your country or region:"
    select country_name in "${countries_name[@]}"; do
      if contains_element "$country_name" "${countries_name[@]}"; then
        country_code=${countries_code[$(( $REPLY - 1 ))]}
        break
      else
        invalid_option
      fi
    done
  }
  OPTION=n
  country_list

  echo "This installer will download files. Please don't disconnect the network."
  pause_function

  url="https://www.archlinux.org/mirrorlist/?country=${country_code}&use_mirror_status=on"

  tmpfile=$(mktemp --suffix=-mirrorlist)
  _exit=0
  while [ ${_exit} -eq 0 ]
  do
    # Get latest mirror list and save to tmpfile
    curl -so ${tmpfile} ${url}

    # Backup and replace current mirrorlist file (if new file is non-zero)
    if [[ -s ${tmpfile} ]]; then
     { echo " Backing up old list..."
       mv -fb /etc/pacman.d/mirrorlist /etc/pacman.d/mirrorlist~; 
     } &&
     { echo " Rotating the new list into place..."
       awk '{sub("^#Server","Server");print}' ${tmpfile} > /etc/pacman.d/mirrorlist
       rm -rf ${tmpfile}
     } && _exit=1
    else
    { echo " Could not download list. Retry in 5 seconds."
	    sleep 5
	}
    fi
  done
}
configure_sudo(){
  echo "Configure sudo..."
  sudoers_path='/etc/sudoers'
  chmod +w ${sudoers_path}
  sed -i '/%wheel ALL=(ALL) ALL/{s/^# //}' ${sudoers_path}
  chmod -w ${sudoers_path}
}
install_basesystem() {
  echo "Configure pacman..."
  pacman-key --init
  pacman-key --populate archlinux
  echo "Install archlinuxcn-keyring..."
  pacman -Syyu --noconfirm archlinuxcn-keyring
  echo "Install basesystem and fakeroot-tcp..."
  pacman -Syyu --noconfirm fakeroot-tcp base base-devel
}

configure_mirrorlist
install_basesystem
configure_sudo