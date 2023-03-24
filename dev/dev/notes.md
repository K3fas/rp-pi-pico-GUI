## SPI + VGA Problems
- IRQ handler nejde nastavit pre sd kartu ked je inicializovana VGA knihovna
  - zmeneny DMA IRQ kanal v spi.c ??? alebo vo VGA kniznici ? ani jedno nefunguje ... nechodi IRQ na VGA scanline
  - zmenene DMA IRQ v spi.c na IRQ1 a v qvga settingoch zmenene DMA kanaly na 8 a 9 nech sa nebiju o ne z DMA pre SPI zbernicu
- FIXED

## Include hell resolve ???
- Pri includnuti vgalib pisti usb kniznica 
- Incluovanie IVGA v kombinacii z vga_lib nadava na undefined sCanvas .... pri pouziti zvlast funguje
#

## DATABINDING
pridany zatial do button a checkbox



## SD example, praca zo zlockami atd example...
- na sd bitmapa a z nej vga kniznica zobrazi na monitoru 
- prerobit raspPicoImg a Snd ... 
- nemecek postup prace z obrazkami 
- runtime preklad obrazkou z bmp


# UPDATE SDK 