#include <stdio.h>
#include <stdlib.h>

typedef enum {
	MALE,
	FEMALE,
	DONT_KNOW,
} SEX;

typedef struct {
	char name[20];
	SEX sex;
	void (*makeASound)(void);
} animal_typdedef;

/**
  * @brief  Ham thuc hien hanh dong keu cua meo
  * @param  None
  * @retval None
  */
void catSound(void) {
	printf("Meo meo\n");
}

/**
  * @brief  Ham thuc hien hanh dong keu cua cho
  * @param  None
  * @retval None
  */
void dogSound(void) {
	printf("Gau gau\n");
}

/**
  * @brief  Ham thuc hien hanh dong keu cua khi
  * @param  None
  * @retval None
  */
void monkeySound(void) {
	printf("Kec kec\n");
}

int main(int argc, char *argv[])
{
    int ret = 0;

    printf("Hello\n");

    animal_typdedef Cat = {
        .name = "Tom",
        .sex = MALE,
        .makeASound = catSound
    };

    animal_typdedef Dog = {
        .name = "Snoopy",
        .sex = MALE,
        .makeASound = dogSound
    };

    animal_typdedef Monkey = {
        .name = "Abu",
        .sex = MALE,
        .makeASound = monkeySound
    };

    Cat.makeASound();
    Dog.makeASound();
    Monkey.makeASound();

    return ret;
}