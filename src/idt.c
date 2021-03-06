#include "idt.h"
#include "util.h"

idt_entry_t idt[IDT_SIZE] = { 0 };
idt_ptr_t pIDT;

/** idt_set_gate
 *  Initialize a idt entry by given index and params
 *
 *  @param index The index of the enrty (in idt)
 *  @param base  The base addr of the entry
 *  @param limit The limit of the entry (highest addr)
 *  @param access and gran The flags of the entry
 */
void set_idt_gate(uint8_t index, uint32_t base, uint16_t seg, uint8_t flags)
{
  idt_entry_t *currEntry = idt + index;

  currEntry->baseLow  = base & 0xFFFF;
  currEntry->baseHigh = (base >> 16) & 0xFFFF;
  currEntry->seg = seg;
  currEntry->flags = flags;

}

/** init_idt
 *  Sets idt
 */
void init_idt()
{
  pIDT.limit = (sizeof(idt_entry_t) * IDT_SIZE) - 1;
  pIDT.base  = (uint32_t) &idt;

  (void) memset(&idt, 0, sizeof(idt_entry_t) * IDT_SIZE); // wipe the idt entries

  global_log(INFO, "Initialized The Interrupt Descriptor Table");
  load_idt();
  global_log(INFO, "Loaded The Interrupt Descriptor Table");

}
