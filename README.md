# decompress
a r package dedicated to decomprsing lzma files

# how to build
you will need rtools and rstuido at first place

make your build tools in system path

go to src/lzma fold and make(it will build the lzma dll and put it in the right place)

then open the project file in Rstudio and build,that's it!

Have fun!

# internals
here is some details for those really curious guys.

we split the original .csv file to  new standard ones(each instrument has a file ) and compress them to a small size(save disk usage and trans time over network,when you have ten years of tick data to transport on a 100Mbps,it's really reallly very slow).

We use lzma for our compress/decompress algorithm,but with some variations.This is how we organize the compressed format:5 byte header to denote file is valid,8 byte lenght denotes how long is the data field and the rest are the compressed data.

This format is compatible with most compress/decomprss tools(such as haoZip,winRar),so it's ok to save the data to a file and open it with haoZip to have a quick look.

  desc 5B len 8B         data
  
  |-----|--------|---xxxxxxxxxxxxx---|
  
