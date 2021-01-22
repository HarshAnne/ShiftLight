# Shift Light V0.3

## J-Link (options 1) 
This is my preferred method for flashing.  
You will need to install the latest J-Link software from Segger's website.  
[(https://www.segger.com/downloads/flasher/)](https://www.segger.com/downloads/flasher/)  
Download the latest software pack for your system, in my case deb-64bit.
After downloading the .deb file, install it using the following command:  
`sudo dpkg -i JLink_Linux_V686f_x86_64.deb`  
The JLink files will be installed here:
`/opt/SEGGER/JLink`  
Run JLink via command line:  
`JLinkExe`

## ST-Link (option 2)
Dependencies:  
`sudo apt-get install git make cmake libusb-1.0-0-dev`  
`sudo apt-get install gcc build-essential`  

Then navigate to the `stlink` folder, or alternatively clone it from the following repository:
`git clone https://github.com/stlink-org/stlink`  

Then navigate into the stlink/ directory.  
`cd stlink`  

Next build the ST-Link utilities.  
`cmake .`  
`make`  




