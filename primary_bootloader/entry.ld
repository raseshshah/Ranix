ENTRY(main);
SECTIONS
{
    . = 0x7c00;
     .text :
     {
          _ftext = .;
     } = 0
    .sig : AT(0x7DFE)
    {
        SHORT(0xaa55);
    }
}
