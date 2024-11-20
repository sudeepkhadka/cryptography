#include <memory.h>
#include <stdint.h>
#include <stdio.h>

#define low_16(address) (uint16_t)((addresss) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)
#define IRQ1 33

char *exception_msgs[] = {"divide by zero", "Debug", "Reserved"};

typedef struct
{
    uint32_t ds; // data segment selector
    // general purpose registers pushed by pusha
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    // pushed by the isr procedure
    uint32_t int_no, err_code;
    // pushed by CPU automatically
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

typedef void (*isr_t)(registers_t *);

isr_t interrupt_handlers[256];

typedef struct
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_registers_t;

idt_registers_t idt_reg;

typedef struct
{
    uint8_t flags;
    uint8_t always0;
    uint16_t selector;
    uint16_t low_offset;
    uint16_t high_offset;
} __attribute__((packed)) idt_gate_t;

void irq_handler(registers_t *r)
{
    if (interrupt_handlers[r->int_no] != 0)
    {
        isr_t handler = interrupt_handlers[r->int_no];
        handler(r);
    }

    port_byte_out(0x20, 0x20); // primary EOI
    if (r->int_no < 40)
    {
        port_byte_out(0xA0, 0x20); // secondary EOI
    }
}

void load_idt()
{
    idt_reg.base = (uint32_t)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    asm volatile("lidt %0" : : "r"(&idt_reg));
}

void isr_install()
{
    // internal ISRs
    set_idt_gate(0, (uint32_t)isr0);
    set_idt_gate(1, (uint32_t)isr1);
    set_idt_gate(2, (uint32_t)isr2);
    set_idt_gate(3, (uint32_t)isr3);
    set_idt_gate(4, (uint32_t)isr4);
    set_idt_gate(5, (uint32_t)isr5);
    set_idt_gate(6, (uint32_t)isr6);
    set_idt_gate(7, (uint32_t)isr7);
    set_idt_gate(8, (uint32_t)isr8);
    set_idt_gate(9, (uint32_t)isr9);
    set_idt_gate(10, (uint32_t)isr10);
    set_idt_gate(11, (uint32_t)isr11);
    //.. up to 31
    set_idt_gate(31, (uint32_t)isr31);

    // ICW1
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);

    // ICW2
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);

    // ICW3
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);

    // ICW4
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);

    // OCW1
    port_byte_out(0x21, 0x00);
    port_byte_out(0xA1, 0x00);

    load_idt();
}

void print_letter(uint8_t scancode)
{
    switch (scancode)
    {
    case 0x0:
        printf("ERROR!");
        break;

    case 0x1:
        printf("ESC");
        break;

    case 0x2:
        printf("1");
        break;

    case 0x39:
        printf("Space");
        break;

    case 0x3:
        printf("2");
        break;

    default:
        if (0x7f > scancode)
        {
            printf("%c -Unknown key pressed", scancode);
            fflush(stdin);
        }
        else if (scancode <= 0x39 + 0x80)
        {
            printf("Key up");
        }
        else
        {
            printf("unknown key up");
        }

        break;
    }
}

void print_nl()
{
    printf("\n");
}

void keyboard_callback(registers_t *regs)
{
    uint8_t scancode = port_byte_in(0x60); // read scancode from the keyboard handler
    print_letter(scancode);
    print_nl();
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, (uint32_t)keyboard_callback);
}

// new kernel function

void main()
{
    clear_screen();
    print_string("Installing interrupt service routines (ISRs).\n");
    isr_install();

    print_string("Enabling external interrupts.\n");
    asm volatile("sti");

    print_string("Initializing keyboard (IRQ 1).\n");
    init_keyboard();
}