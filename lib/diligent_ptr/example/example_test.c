#include "example_driver.h"

#define USE_DILIGENT_PTR	//실제 환경에선 build script(Shell Script, Makefile, CMakeLists.txt 등)에서 관리된다.
#ifdef USE_DILIGENT_PTR
	#include "diligent_ptr.h"
	extern struct diligent_ptr < struct mmio_map > sfr_regs; //driver의 diligent_ptr를 사용할 수 있도록 extern 변수를 선언한다.
	static struct mmio_map real_map_stuff;
	static struct mmio_map *real_map = &real_map_stuff;		//driver가 접근할 sfr 영역이다. 실제 환경에선 해당 address로 대체된다.
#else
	static struct mmio_map *real_map = MMIO_MAP_BASE_ADDRESS;

	#define PUSH_EXPECT_READ_AND_RETURN(sfr_regs, val)
	#define PUSH_COMPARE_SNAPSHOT(sfr_regs, val)
	#define CLEAR_SNAPSHOT_ARR(sfr_regs)
	#define VERIFY(sfr_regs)
#endif //USE_DILIGENT_PTR

int main(void)
{
	int result, expected;
	struct mmio_map sample = {};			//각 -> 사용마다 비교할 기대 값을 설정하기 위한 임시 변수이다.

	CLEAR_SNAPSHOT_ARR(sfr_regs);					//snapshot array를 모두 비운다.

	PUSH_EXPECT_READ_AND_RETURN(sfr_regs, &sample);	//첫 번째 ->에 대한 기대 값을 설정한다. 모든 멤버 변수가 0이다.
	PUSH_EXPECT_READ_AND_RETURN(sfr_regs, &sample);	//두 번째 ->에 대한 기대 값을 설정한다. 모든 멤버 변수가 0이다.
	sample.b.bb = 1;
	PUSH_COMPARE_SNAPSHOT(sfr_regs, &sample);			//세 번째 ->에서 compare할 snapshot을 추가한다.
	PUSH_EXPECT_READ_AND_RETURN(sfr_regs, &sample);	//세 번째 ->에 대한 기대 값을 설정한다. 이때 b.bb=1 일 것을 기대한다.
	sample.c.ccc = 2;
	PUSH_COMPARE_SNAPSHOT(sfr_regs, &sample);			//네 번째 ->에서 compare할 snapshot을 추가한다.
	PUSH_EXPECT_READ_AND_RETURN(sfr_regs, &sample);	//네 번째 ->에 대한 기대 값을 설정한다. 이때 b.bb=1이고 c.ccc=2 일 것을 기대한다.
	PUSH_EXPECT_READ_AND_RETURN(sfr_regs, &sample);	//다섯 번째 ->에 대한 기대 값을 설정한다. 이때 b.bb=1이고 c.ccc=2 일 것을 기대한다.

	//여기부터 test할 drvier code가 호출된다.
	result = driver_init(real_map);			//driver를 초기화하고 sfr 영역을 할당한다. 여기서 test main에 지역 변수로 할당된 sfr 영역이 driver의 diligent_ptr에 연결된다.
	expected = 0;
	if (result != expected) do {} while (1);

	result = driver_func();					//driver_func 호출되며 sfr 접근(->)이 발생한다. -> 사용 시마다 미리 설정된 기대 값이 반환 되고 compare가 설정된 경우 기대 값과 같은지 비교한다.
	expected = 0;
	if (result != expected) do {} while (1);

	VERIFY(sfr_regs);								//최종 map이 기대 값과 같은지 확인하고, 설정된 만큼 -> 호출이 발생했는지 확인한다.
											//마지막 compare가 진행되지 않았을 경우 이때 진행된다.(마지막 ->가 write로 사용된 경우)
	return 0;
}
