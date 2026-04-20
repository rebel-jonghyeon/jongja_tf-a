#ifndef IMAGE_H
#define IMAGE_H

void jump_to_next_image(uint64_t addr)
{
	((void (*)(void))addr) ();
}

#endif /* IMAGE_H */
