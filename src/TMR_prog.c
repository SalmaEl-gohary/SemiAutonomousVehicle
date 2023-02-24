/*
 * TMR_porg.c
 *
 *  Created on: Feb 3, 2023
 *      Author: salma
 */
#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "TMR_priv.h"
#include "TMR_int.h"




void TMR_voidStart(TMRN_t Copy_uddtTMR_no)
{
	switch(Copy_uddtTMR_no)
	{
	case TMR2:
		SET_BIT(TMR2_ADD -> CR1, CEN_BIT); break;
	case TMR3:
		SET_BIT(TMR3_ADD -> CR1, CEN_BIT); break;
	case TMR4:
		SET_BIT(TMR4_ADD -> CR1, CEN_BIT); break;
	case TMR5:
		SET_BIT(TMR5_ADD -> CR1, CEN_BIT); break;

	default:                               break;
	}
}

void TMR_voidSetPrescaler(TMRN_t Copy_uddtTMR_no, u16 Copy_u16Value)
{
	switch(Copy_uddtTMR_no)
	{
	case TMR2:
		Clr_ALL_BITS(TMR2_ADD -> PSC);
		TMR2_ADD -> PSC |= Copy_u16Value;
		break;
	case TMR3:
		Clr_ALL_BITS(TMR3_ADD -> PSC);
		TMR3_ADD -> PSC |= Copy_u16Value;
		break;
	case TMR4:
		Clr_ALL_BITS(TMR4_ADD -> PSC);
		TMR4_ADD -> PSC |= Copy_u16Value;
		break;
	case TMR5:
		Clr_ALL_BITS(TMR5_ADD -> PSC);
		TMR5_ADD -> PSC |= Copy_u16Value;
		break;
	default:                               break;
	}
}




void TMR_voidSetChannelOutput(TMRN_t Copy_uddtTMR_no, CMPFn_t Copy_uddtFn, CHN_t Copy_uddtChNo)
{
	switch(Copy_uddtTMR_no)
	{
	case TMR2:
		switch(Copy_uddtChNo)
		{
		case CH1:
			CLR_BITS(TMR2_ADD -> CCMR1, 0x0073);
			TMR2_ADD -> CCMR1 |= (Copy_uddtFn << OC1M_SHIFT);
			SET_BIT(TMR2_ADD -> CCER, CC1EN_BIT);
			break;
		case CH2:
			CLR_BITS(TMR2_ADD -> CCMR1, 0x7300);
			TMR2_ADD -> CCMR1 |= (Copy_uddtFn << OC2M_SHIFT);
			SET_BIT(TMR2_ADD -> CCER, CC2EN_BIT);
			break;
		case CH3:
			CLR_BITS(TMR2_ADD -> CCMR2, 0x0073);
			TMR2_ADD -> CCMR2 |= (Copy_uddtFn << OC3M_SHIFT);
			SET_BIT(TMR2_ADD -> CCER, CC3EN_BIT);
			break;
		case CH4:
			CLR_BITS(TMR2_ADD -> CCMR2, 0x7300);
			TMR2_ADD -> CCMR2 |= (Copy_uddtFn << OC4M_SHIFT);
			SET_BIT(TMR2_ADD -> CCER, CC4EN_BIT);
			break;
		}
		break;
		case TMR3:
			switch(Copy_uddtChNo)
			{
			case CH1:
				CLR_BITS(TMR3_ADD -> CCMR1, 0x0073);
				TMR3_ADD -> CCMR1 |= (Copy_uddtFn << OC1M_SHIFT);
				SET_BIT(TMR3_ADD -> CCER, CC1EN_BIT);
				break;
			case CH2:
				CLR_BITS(TMR3_ADD -> CCMR1, 0x7300);
				TMR3_ADD -> CCMR1 |= (Copy_uddtFn << OC2M_SHIFT);
				SET_BIT(TMR3_ADD -> CCER, CC2EN_BIT);
				break;
			case CH3:
				CLR_BITS(TMR3_ADD -> CCMR2, 0x0073);
				TMR3_ADD -> CCMR2 |= (Copy_uddtFn << OC3M_SHIFT);
				SET_BIT(TMR3_ADD -> CCER, CC3EN_BIT);
				break;
			case CH4:
				CLR_BITS(TMR3_ADD -> CCMR2, 0x7300);
				TMR3_ADD -> CCMR2 |= (Copy_uddtFn << OC4M_SHIFT);
				SET_BIT(TMR3_ADD -> CCER, CC4EN_BIT);
				break;
			}
			break;
			case TMR4:
				switch(Copy_uddtChNo)
				{
				case CH1:
					CLR_BITS(TMR4_ADD -> CCMR1, 0x0073);
					TMR4_ADD -> CCMR1 |= (Copy_uddtFn << OC1M_SHIFT);
					SET_BIT(TMR4_ADD -> CCER, CC1EN_BIT);
					break;
				case CH2:
					CLR_BITS(TMR4_ADD -> CCMR1, 0x7300);
					TMR4_ADD -> CCMR1 |= (Copy_uddtFn << OC2M_SHIFT);
					SET_BIT(TMR4_ADD -> CCER, CC2EN_BIT);
					break;
				case CH3:
					CLR_BITS(TMR4_ADD -> CCMR2, 0x0073);
					TMR4_ADD -> CCMR2 |= (Copy_uddtFn << OC3M_SHIFT);
					SET_BIT(TMR4_ADD -> CCER, CC3EN_BIT);
					break;
				case CH4:
					CLR_BITS(TMR4_ADD -> CCMR2, 0x7300);
					TMR4_ADD -> CCMR2 |= (Copy_uddtFn << OC4M_SHIFT);
					SET_BIT(TMR4_ADD -> CCER, CC4EN_BIT);
					break;
				}
				break;
				case TMR5:
					switch(Copy_uddtChNo)
					{
					case CH1:
						CLR_BITS(TMR5_ADD -> CCMR1, 0x0073);
						TMR5_ADD -> CCMR1 |= (Copy_uddtFn << OC1M_SHIFT);
						SET_BIT(TMR5_ADD -> CCER, CC1EN_BIT);
						break;
					case CH2:
						CLR_BITS(TMR5_ADD -> CCMR1, 0x7300);
						TMR5_ADD -> CCMR1 |= (Copy_uddtFn << OC2M_SHIFT);
						SET_BIT(TMR5_ADD -> CCER, CC2EN_BIT);
						break;
					case CH3:
						CLR_BITS(TMR5_ADD -> CCMR2, 0x0073);
						TMR5_ADD -> CCMR2 |= (Copy_uddtFn << OC3M_SHIFT);
						SET_BIT(TMR5_ADD -> CCER, CC3EN_BIT);
						break;
					case CH4:
						CLR_BITS(TMR5_ADD -> CCMR2, 0x7300);
						TMR5_ADD -> CCMR2 |= (Copy_uddtFn << OC4M_SHIFT);
						SET_BIT(TMR5_ADD -> CCER, CC4EN_BIT);
						break;
					}
					break;
	default:                               break;
	}
}




void TMR_voidSetCMPVal(TMRN_t Copy_uddtTMR_no, CHN_t Copy_uddtChNo, u32 cmpValue)
{
	switch(Copy_uddtTMR_no)
	{
	case TMR2:
		switch(Copy_uddtChNo)
		{
		case CH1:
			TMR2_ADD -> CCR1 = cmpValue;
			break;
		case CH2:
			TMR2_ADD -> CCR2 = cmpValue;
			break;
		case CH3:
			TMR2_ADD -> CCR3 = cmpValue;
			break;
		case CH4:
			TMR2_ADD -> CCR4 = cmpValue;
			break;
		}
		break;
		case TMR3:
			switch(Copy_uddtChNo)
			{
			case CH1:
				TMR3_ADD -> CCR1 = cmpValue;
				break;
			case CH2:
				TMR3_ADD -> CCR2 = cmpValue;
				break;
			case CH3:
				TMR3_ADD -> CCR3 = cmpValue;
				break;
			case CH4:
				TMR3_ADD -> CCR4 = cmpValue;
				break;
			}
			break;
			case TMR4:
				switch(Copy_uddtChNo)
				{
				case CH1:
					TMR4_ADD -> CCR1 = cmpValue;
					break;
				case CH2:
					TMR4_ADD -> CCR2 = cmpValue;
					break;
				case CH3:
					TMR4_ADD -> CCR3 = cmpValue;
					break;
				case CH4:
					TMR4_ADD -> CCR4 = cmpValue;
					break;
				}
				break;
				case TMR5:
					switch(Copy_uddtChNo)
					{
					case CH1:
						TMR5_ADD -> CCR1 = cmpValue;
						break;
					case CH2:
						TMR5_ADD -> CCR2 = cmpValue;
						break;
					case CH3:
						TMR5_ADD -> CCR3 = cmpValue;
						break;
					case CH4:
						TMR5_ADD -> CCR4 = cmpValue;
						break;
					}
					break;
	default:                               break;
	}
}







void TMR_voidSetARR(TMRN_t Copy_uddtTMR_no, u32 Copy_u32Value)
{
	switch(Copy_uddtTMR_no)
	{
	case TMR2:
		TMR2_ADD -> ARR = Copy_u32Value;
		break;
	case TMR3:
		TMR3_ADD -> ARR = Copy_u32Value;
		break;
	case TMR4:
		TMR4_ADD -> ARR = Copy_u32Value;
		break;
	case TMR5:
		TMR5_ADD -> ARR = Copy_u32Value;
		break;
	default:                               break;
	}
}



void TMR_voidClearCount(TMRN_t Copy_uddtTMR_no)
{
	switch(Copy_uddtTMR_no)
	{
	case TMR2:
		TMR2_ADD -> CNT = 0;
		break;
	case TMR3:
		TMR3_ADD -> CNT = 0;
		break;
	case TMR4:
		TMR4_ADD -> CNT = 0;
		break;
	case TMR5:
		TMR5_ADD -> CNT = 0;
		break;
	default:                               break;
	}
}

void TMR_voidEnableICUInt(TMRN_t Copy_uddtTMR_no)
{
	switch(Copy_uddtTMR_no)
	{
	case TMR2:
		SET_BIT(TMR2_ADD -> DIER, 2);
		break;
	case TMR3:
		SET_BIT(TMR3_ADD -> DIER, 1);
		break;
	case TMR4:
		SET_BIT(TMR4_ADD -> DIER, 1);
		break;
	case TMR5:
		SET_BIT(TMR5_ADD -> DIER, 1);
		break;
	}
}




void TMR_voidSetChannelInput(TMRN_t Copy_uddtTMR_no, CHN_t Copy_uddtCH_no)
{
	switch(Copy_uddtTMR_no)
	{
	case TMR2:
		switch(Copy_uddtCH_no)
		{
		case CH1:
			CLR_BITS(TMR2_ADD -> CCMR1, 0x0003);
			SET_BIT(TMR2_ADD -> CCMR1, CC1S_SHIFT);

			#if ICU_TRIG == BOTH
				SET_BIT(TMR2_ADD -> CCER, CC1P_BIT);
				SET_BIT(TMR2_ADD -> CCER, CC1NP_BIT);
			#endif

			SET_BIT(TMR2_ADD -> CCER, CC1EN_BIT);
			break;
		case CH2:
			CLR_BITS(TMR2_ADD -> CCMR1, 0x0300);
			SET_BIT(TMR2_ADD -> CCMR1, CC2S_SHIFT);

			#if ICU_TRIG == BOTH
				SET_BIT(TMR2_ADD -> CCER, CC2P_BIT);
				SET_BIT(TMR2_ADD -> CCER, CC2NP_BIT);
			#endif

			SET_BIT(TMR2_ADD -> CCER, CC2EN_BIT);
			break;
		case CH3:
			CLR_BITS(TMR2_ADD -> CCMR2, 0x0003);
			SET_BIT(TMR2_ADD -> CCMR2, CC3S_SHIFT);

			#if ICU_TRIG == BOTH
				SET_BIT(TMR2_ADD -> CCER, CC3P_BIT);
				SET_BIT(TMR2_ADD -> CCER, CC3NP_BIT);
			#endif

			SET_BIT(TMR2_ADD -> CCER, CC3EN_BIT);
			break;
		case CH4:
			CLR_BITS(TMR2_ADD -> CCMR2, 0x0300);
			SET_BIT(TMR2_ADD -> CCMR2, CC4S_SHIFT);

			#if ICU_TRIG == BOTH
				SET_BIT(TMR2_ADD -> CCER, CC4P_BIT);
				SET_BIT(TMR2_ADD -> CCER, CC4NP_BIT);
			#endif

			SET_BIT(TMR2_ADD -> CCER, CC4EN_BIT);
			break;
		}
		break;
	case TMR3:
		switch(Copy_uddtCH_no)
		{
		case CH1:
			CLR_BITS(TMR3_ADD -> CCMR1, 0x0003);
			SET_BIT(TMR3_ADD -> CCMR1, CC1S_SHIFT);

		#if ICU_TRIG == BOTH
			SET_BIT(TMR3_ADD -> CCER, CC1P_BIT);
			SET_BIT(TMR3_ADD -> CCER, CC1NP_BIT);
		#endif

			SET_BIT(TMR3_ADD -> CCER, CC1EN_BIT);
			break;
		case CH2:
			CLR_BITS(TMR3_ADD -> CCMR1, 0x0300);
			SET_BIT(TMR3_ADD -> CCMR1, CC2S_SHIFT);

			#if ICU_TRIG == BOTH
				SET_BIT(TMR3_ADD -> CCER, CC2P_BIT);
				SET_BIT(TMR3_ADD -> CCER, CC2NP_BIT);
			#endif

			SET_BIT(TMR3_ADD -> CCER, CC2EN_BIT);
			break;
		case CH3:
			CLR_BITS(TMR3_ADD -> CCMR2, 0x0003);
			SET_BIT(TMR3_ADD -> CCMR2, CC3S_SHIFT);

			#if ICU_TRIG == BOTH
				SET_BIT(TMR3_ADD -> CCER, CC3P_BIT);
				SET_BIT(TMR3_ADD -> CCER, CC3NP_BIT);
			#endif

			SET_BIT(TMR3_ADD -> CCER, CC3EN_BIT);
			break;
		case CH4:
			CLR_BITS(TMR3_ADD -> CCMR2, 0x0300);
			SET_BIT(TMR3_ADD -> CCMR2, CC4S_SHIFT);

			#if ICU_TRIG == BOTH
				SET_BIT(TMR3_ADD -> CCER, CC4P_BIT);
				SET_BIT(TMR3_ADD -> CCER, CC4NP_BIT);
			#endif

			SET_BIT(TMR3_ADD -> CCER, CC4EN_BIT);
			break;
		}
		break;
	case TMR4:
		switch(Copy_uddtCH_no)
		{
		case CH1:
			CLR_BITS(TMR4_ADD -> CCMR1, 0x0003);
			SET_BIT(TMR4_ADD -> CCMR1, CC1S_SHIFT);

		#if ICU_TRIG == BOTH
			SET_BIT(TMR4_ADD -> CCER, CC1P_BIT);
			SET_BIT(TMR4_ADD -> CCER, CC1NP_BIT);
		#endif

			SET_BIT(TMR4_ADD -> CCER, CC1EN_BIT);
			break;
		case CH2:
			CLR_BITS(TMR4_ADD -> CCMR1, 0x0300);
			SET_BIT(TMR4_ADD -> CCMR1, CC2S_SHIFT);

			#if ICU_TRIG == BOTH
				SET_BIT(TMR4_ADD -> CCER, CC2P_BIT);
				SET_BIT(TMR4_ADD -> CCER, CC2NP_BIT);
			#endif

			SET_BIT(TMR4_ADD -> CCER, CC2EN_BIT);
			break;
		case CH3:
			CLR_BITS(TMR4_ADD -> CCMR2, 0x0003);
			SET_BIT(TMR4_ADD -> CCMR2, CC3S_SHIFT);

			#if ICU_TRIG == BOTH
				SET_BIT(TMR4_ADD -> CCER, CC3P_BIT);
				SET_BIT(TMR4_ADD -> CCER, CC3NP_BIT);
			#endif

			SET_BIT(TMR4_ADD -> CCER, CC3EN_BIT);
			break;
		case CH4:
			CLR_BITS(TMR4_ADD -> CCMR2, 0x0300);
			SET_BIT(TMR4_ADD -> CCMR2, CC4S_SHIFT);

			#if ICU_TRIG == BOTH
				SET_BIT(TMR4_ADD -> CCER, CC4P_BIT);
				SET_BIT(TMR4_ADD -> CCER, CC4NP_BIT);
			#endif

			SET_BIT(TMR4_ADD -> CCER, CC4EN_BIT);
			break;
		}
		break;
	case TMR5:
		switch(Copy_uddtCH_no)
		{
		case CH1:
			CLR_BITS(TMR5_ADD -> CCMR1, 0x0003);
			SET_BIT(TMR5_ADD -> CCMR1, CC1S_SHIFT);

		#if ICU_TRIG == BOTH
			SET_BIT(TMR5_ADD -> CCER, CC1P_BIT);
			SET_BIT(TMR5_ADD -> CCER, CC1NP_BIT);
		#endif

			SET_BIT(TMR5_ADD -> CCER, CC1EN_BIT);
			break;
		case CH2:
			CLR_BITS(TMR5_ADD -> CCMR1, 0x0300);
			SET_BIT(TMR5_ADD -> CCMR1, CC2S_SHIFT);

			#if ICU_TRIG == BOTH
				SET_BIT(TMR5_ADD -> CCER, CC2P_BIT);
				SET_BIT(TMR5_ADD -> CCER, CC2NP_BIT);
			#endif

			SET_BIT(TMR5_ADD -> CCER, CC2EN_BIT);
			break;
		case CH3:
			CLR_BITS(TMR5_ADD -> CCMR2, 0x0003);
			SET_BIT(TMR5_ADD -> CCMR2, CC3S_SHIFT);

			#if ICU_TRIG == BOTH
				SET_BIT(TMR5_ADD -> CCER, CC3P_BIT);
				SET_BIT(TMR5_ADD -> CCER, CC3NP_BIT);
			#endif

			SET_BIT(TMR5_ADD -> CCER, CC3EN_BIT);
			break;
		case CH4:
			CLR_BITS(TMR5_ADD -> CCMR2, 0x0300);
			SET_BIT(TMR5_ADD -> CCMR2, CC4S_SHIFT);

			#if ICU_TRIG == BOTH
				SET_BIT(TMR5_ADD -> CCER, CC4P_BIT);
				SET_BIT(TMR5_ADD -> CCER, CC4NP_BIT);
			#endif

			SET_BIT(TMR5_ADD -> CCER, CC4EN_BIT);
			break;
		}
		break;
	}
}

u32 TMR_voidReadCapture(TMRN_t Copy_uddtTMR_no, CHN_t Copy_uddtChNo)
{
	u32 reading = 0;
	switch(Copy_uddtTMR_no)
	{
	case TMR2:
		switch(Copy_uddtChNo)
		{
		case CH1:
			reading = TMR2_ADD -> CCR1;
			break;
		case CH2:
			reading = TMR2_ADD -> CCR2;
			break;
		case CH3:
			reading = TMR2_ADD -> CCR3;
			break;
		case CH4:
			reading = TMR2_ADD -> CCR4;
			break;
		}
		break;

	case TMR3:
		switch(Copy_uddtChNo)
		{
		case CH1:
			reading = TMR3_ADD -> CCR1;
			break;
		case CH2:
			reading = TMR3_ADD -> CCR2;
			break;
		case CH3:
			reading = TMR3_ADD -> CCR3;
			break;
		case CH4:
			reading = TMR3_ADD -> CCR4;
			break;
		}
		break;
	case TMR4:
		switch(Copy_uddtChNo)
		{
		case CH1:
			reading = TMR4_ADD -> CCR1;
			break;
		case CH2:
			reading = TMR4_ADD -> CCR2;
			break;
		case CH3:
			reading = TMR4_ADD -> CCR3;
			break;
		case CH4:
			reading = TMR4_ADD -> CCR4;
			break;
		}
		break;
	case TMR5:
		switch(Copy_uddtChNo)
		{
		case CH1:
			reading = TMR5_ADD -> CCR1;
			break;
		case CH2:
			reading = TMR5_ADD -> CCR2;
			break;
		case CH3:
			reading = TMR5_ADD -> CCR3;
			break;
		case CH4:
			reading = TMR5_ADD -> CCR4;
			break;
		}
		break;
	default:                               break;
	}
	return reading;
}

void TMR_vidEnableOVFInt(TMRN_t Copy_uddtTMR_no)
{
	switch(Copy_uddtTMR_no)
	{
	case TMR2:
		SET_BIT(TMR2_ADD -> DIER, UIE_BIT);
		break;
	case TMR3:
		SET_BIT(TMR3_ADD -> DIER, UIE_BIT);

		break;
	case TMR4:
		SET_BIT(TMR4_ADD -> DIER, UIE_BIT);

		break;
	case TMR5:
		SET_BIT(TMR5_ADD -> DIER, UIE_BIT);

		break;
	}
}

void TMR_vidClearOvf(TMRN_t Copy_uddtTMR_no)
{
	switch(Copy_uddtTMR_no)
	{
	case TMR2:
		CLR_BIT(TMR2_ADD -> SR, UIE_BIT);
		break;
	case TMR3:
		CLR_BIT(TMR3_ADD -> SR, UIE_BIT);
		break;
	case TMR4:
		CLR_BIT(TMR4_ADD -> SR, UIE_BIT);

		break;
	case TMR5:
		CLR_BIT(TMR5_ADD -> SR, UIE_BIT);

		break;
	}
}


u8 TMR_u8GetOVF(TMRN_t Copy_uddtTMR_no)
{
	u8 flag = 0;
	switch(Copy_uddtTMR_no)
	{

	case TMR2:
		flag = GET_BIT(TMR2_ADD -> SR, UIE_BIT);
		break;
	case TMR3:
		flag = GET_BIT(TMR3_ADD -> SR, UIE_BIT);
		break;
	case TMR4:
		flag = GET_BIT(TMR4_ADD -> SR, UIE_BIT);

		break;
	case TMR5:
		flag = GET_BIT(TMR5_ADD -> SR, UIE_BIT);

		break;
	}
	return flag;
}

u8 TMR_u8GetCC1IF(TMRN_t Copy_uddtTMR_no)
{
	u8 flag = 0;
	switch(Copy_uddtTMR_no)
	{

	case TMR2:
		flag = GET_BIT(TMR2_ADD -> SR, 1);
		break;
	case TMR3:
		flag = GET_BIT(TMR3_ADD -> SR, 1);
		break;
	case TMR4:
		flag = GET_BIT(TMR4_ADD -> SR, 1);

		break;
	case TMR5:
		flag = GET_BIT(TMR5_ADD -> SR, 1);

		break;
	}
	return flag;
}







