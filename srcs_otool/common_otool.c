#include "ft_otool.h"

static void print_value(int n, t_otool_env *e)
{
	// printf("lib = %d, cpu = %d\n", e->lib, e->fat);
	if (e->dylink && e->cpu == 64)
		ft_printf("%08x%08x", 0x0000ffff - 0x8000 , n); // wtf
	else if (e->lib || (e->cpu == 32 && e->fat == 1))
		ft_printf("00000000%08x", n);
	else if (e->cpu == 64)
		ft_printf("00000001%08x", n);
	else if (e->cpu == 32)
		ft_printf("%08x" , n);

}

void	print_dat_shit(uint32_t size, uint32_t addr, char *offset, t_otool_env *e)
{
	uint32_t 	n;
	uint32_t	i;

	n = 0;
	ft_printf("Contents of (__TEXT,__text) section\n");
	while (n < size)
	{
		print_value(addr + n, e);
		ft_printf("\t");
		i = 0;
		while (i < 16 && n + i < size)
		{
			ft_printf("%.2x ", (unsigned char)(offset[n + i]));
			i++;
		}
		ft_printf("\n");
		n += i;		
	}
}