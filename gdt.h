#ifndef __GDT_H
#define __GDT_H

    #include "types.h"
    
    class GlobalDescriptorTable
    {
        public:

            class SegmentDescriptor
            {
                private:
                    uint16_t limit_lo;
                    uint16_t base_lo;
                    uint8_t base_hi;
                    uint8_t type;
                    uint8_t limit_hi;
                    uint8_t base_vhi;

                public:
                    SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type); //get regular base and limits
                    uint32_t Base();//method to return base value
                    uint32_t Limit();//method to return limit value
            } __attribute__((packed)); /*makes sure that the class will be laid out how 
            we want it to, compiler will not be able to move object around a bit to gain performance */

        private:
            SegmentDescriptor nullSegmentSelector;//empty
            SegmentDescriptor unusedSegmentSelector;//unused
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

        public:

            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            uint16_t CodeSegmentSelector();//returns offset of codesegement
            uint16_t DataSegmentSelector();//returns offset of datasegment
    };

#endif