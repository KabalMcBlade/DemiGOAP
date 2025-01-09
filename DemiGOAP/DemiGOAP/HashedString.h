// Copyright (c) 2020-2025 Michele Condo'
// File: C:\Projects\DemiGOAP\DemiGOAP\DemiGOAP\HashedString.h
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
#pragma once

#include "Core.h"


DEMIGOAP_NAMESPACE_BEGIN

static constexpr uint32_t kStringOffset = 1092394437;
static constexpr uint32_t kStringPrime = 8389011;


class HashedString final
{
private:
	std::string m_value;
	uint32_t m_hash;

public:
	struct ConstCharWrapper
	{
		// Not-explicit constructor on purpose!
		// This forces the compiler to choose the template function right, and avoid implicit conversion
		ConstCharWrapper(const char* _value) : m_value(_value) {}
		const char* m_value;
	};

	template <size_t N>
	explicit HashedString(const char(&_value)[N])
	{
		m_value = _value;
	}

	explicit HashedString(ConstCharWrapper _string) : m_hash(HashedString::StringToHash(_string.m_value, kStringOffset, kStringPrime))
	{
		m_value = _string.m_value;
	}

	explicit HashedString(const HashedString& _other) : m_hash(_other.m_hash), m_value(_other.m_value) {}

	DEMIGOAP_INLINE operator const std::string& () const
	{
		return m_value;
	}

	DEMIGOAP_INLINE operator const uint32_t& () const
	{
		return m_hash;
	}

	static uint32_t StringToHash(const char* _valueToHash, uint32_t _offset, uint32_t _prime)
	{
		uint32_t uiHash = _offset;
		while (*_valueToHash != 0)
		{
			uiHash ^= *_valueToHash++;
			uiHash *= _prime;
		}

		return uiHash;
	}

#define HASHED_STRING_1            kStringOffset
#define HASHED_STRING_2            ((HASHED_STRING_1 ^ _value[0]) * kStringPrime)
#define HASHED_STRING_3            ((HASHED_STRING_2 ^ _value[1]) * kStringPrime)
#define HASHED_STRING_4            ((HASHED_STRING_3 ^ _value[2]) * kStringPrime)
#define HASHED_STRING_5            ((HASHED_STRING_4 ^ _value[3]) * kStringPrime)
#define HASHED_STRING_6            ((HASHED_STRING_5 ^ _value[4]) * kStringPrime)
#define HASHED_STRING_7            ((HASHED_STRING_6 ^ _value[5]) * kStringPrime)
#define HASHED_STRING_8            ((HASHED_STRING_7 ^ _value[6]) * kStringPrime)
#define HASHED_STRING_9            ((HASHED_STRING_8 ^ _value[7]) * kStringPrime)
#define HASHED_STRING_10            ((HASHED_STRING_9 ^ _value[8]) * kStringPrime)
#define HASHED_STRING_11            ((HASHED_STRING_10 ^ _value[9]) * kStringPrime)
#define HASHED_STRING_12            ((HASHED_STRING_11 ^ _value[10]) * kStringPrime)
#define HASHED_STRING_13            ((HASHED_STRING_12 ^ _value[11]) * kStringPrime)
#define HASHED_STRING_14            ((HASHED_STRING_13 ^ _value[12]) * kStringPrime)
#define HASHED_STRING_15            ((HASHED_STRING_14 ^ _value[13]) * kStringPrime)
#define HASHED_STRING_16            ((HASHED_STRING_15 ^ _value[14]) * kStringPrime)
#define HASHED_STRING_17            ((HASHED_STRING_16 ^ _value[15]) * kStringPrime)
#define HASHED_STRING_18            ((HASHED_STRING_17 ^ _value[16]) * kStringPrime)
#define HASHED_STRING_19            ((HASHED_STRING_18 ^ _value[17]) * kStringPrime)
#define HASHED_STRING_20            ((HASHED_STRING_19 ^ _value[18]) * kStringPrime)
#define HASHED_STRING_21            ((HASHED_STRING_20 ^ _value[19]) * kStringPrime)
#define HASHED_STRING_22            ((HASHED_STRING_21 ^ _value[20]) * kStringPrime)
#define HASHED_STRING_23            ((HASHED_STRING_22 ^ _value[21]) * kStringPrime)
#define HASHED_STRING_24            ((HASHED_STRING_23 ^ _value[22]) * kStringPrime)
#define HASHED_STRING_25            ((HASHED_STRING_24 ^ _value[23]) * kStringPrime)
#define HASHED_STRING_26            ((HASHED_STRING_25 ^ _value[24]) * kStringPrime)
#define HASHED_STRING_27            ((HASHED_STRING_26 ^ _value[25]) * kStringPrime)
#define HASHED_STRING_28            ((HASHED_STRING_27 ^ _value[26]) * kStringPrime)
#define HASHED_STRING_29            ((HASHED_STRING_28 ^ _value[27]) * kStringPrime)
#define HASHED_STRING_30            ((HASHED_STRING_29 ^ _value[28]) * kStringPrime)
#define HASHED_STRING_31            ((HASHED_STRING_30 ^ _value[29]) * kStringPrime)
#define HASHED_STRING_32            ((HASHED_STRING_31 ^ _value[30]) * kStringPrime)
#define HASHED_STRING_33            ((HASHED_STRING_32 ^ _value[31]) * kStringPrime)
#define HASHED_STRING_34            ((HASHED_STRING_33 ^ _value[32]) * kStringPrime)
#define HASHED_STRING_35            ((HASHED_STRING_34 ^ _value[33]) * kStringPrime)
#define HASHED_STRING_36            ((HASHED_STRING_35 ^ _value[34]) * kStringPrime)
#define HASHED_STRING_37            ((HASHED_STRING_36 ^ _value[35]) * kStringPrime)
#define HASHED_STRING_38            ((HASHED_STRING_37 ^ _value[36]) * kStringPrime)
#define HASHED_STRING_39            ((HASHED_STRING_38 ^ _value[37]) * kStringPrime)
#define HASHED_STRING_40            ((HASHED_STRING_39 ^ _value[38]) * kStringPrime)
#define HASHED_STRING_41            ((HASHED_STRING_40 ^ _value[39]) * kStringPrime)
#define HASHED_STRING_42            ((HASHED_STRING_41 ^ _value[40]) * kStringPrime)
#define HASHED_STRING_43            ((HASHED_STRING_42 ^ _value[41]) * kStringPrime)
#define HASHED_STRING_44            ((HASHED_STRING_43 ^ _value[42]) * kStringPrime)
#define HASHED_STRING_45            ((HASHED_STRING_44 ^ _value[43]) * kStringPrime)
#define HASHED_STRING_46            ((HASHED_STRING_45 ^ _value[44]) * kStringPrime)
#define HASHED_STRING_47            ((HASHED_STRING_46 ^ _value[45]) * kStringPrime)
#define HASHED_STRING_48            ((HASHED_STRING_47 ^ _value[46]) * kStringPrime)
#define HASHED_STRING_49            ((HASHED_STRING_48 ^ _value[47]) * kStringPrime)
#define HASHED_STRING_50            ((HASHED_STRING_49 ^ _value[48]) * kStringPrime)
#define HASHED_STRING_51            ((HASHED_STRING_50 ^ _value[49]) * kStringPrime)
#define HASHED_STRING_52            ((HASHED_STRING_51 ^ _value[50]) * kStringPrime)
#define HASHED_STRING_53            ((HASHED_STRING_52 ^ _value[51]) * kStringPrime)
#define HASHED_STRING_54            ((HASHED_STRING_53 ^ _value[52]) * kStringPrime)
#define HASHED_STRING_55            ((HASHED_STRING_54 ^ _value[53]) * kStringPrime)
#define HASHED_STRING_56            ((HASHED_STRING_55 ^ _value[54]) * kStringPrime)
#define HASHED_STRING_57            ((HASHED_STRING_56 ^ _value[55]) * kStringPrime)
#define HASHED_STRING_58            ((HASHED_STRING_57 ^ _value[56]) * kStringPrime)
#define HASHED_STRING_59            ((HASHED_STRING_58 ^ _value[57]) * kStringPrime)
#define HASHED_STRING_60            ((HASHED_STRING_59 ^ _value[58]) * kStringPrime) 
#define HASHED_STRING_61            ((HASHED_STRING_60 ^ _value[59]) * kStringPrime)
#define HASHED_STRING_62            ((HASHED_STRING_61 ^ _value[60]) * kStringPrime)
#define HASHED_STRING_63            ((HASHED_STRING_62 ^ _value[61]) * kStringPrime)
#define HASHED_STRING_64            ((HASHED_STRING_63 ^ _value[62]) * kStringPrime)
#define HASHED_STRING_65            ((HASHED_STRING_64 ^ _value[63]) * kStringPrime)
#define HASHED_STRING_66            ((HASHED_STRING_65 ^ _value[64]) * kStringPrime)
#define HASHED_STRING_67            ((HASHED_STRING_66 ^ _value[65]) * kStringPrime)
#define HASHED_STRING_68            ((HASHED_STRING_67 ^ _value[66]) * kStringPrime)
#define HASHED_STRING_69            ((HASHED_STRING_68 ^ _value[67]) * kStringPrime)
#define HASHED_STRING_70            ((HASHED_STRING_69 ^ _value[68]) * kStringPrime)
#define HASHED_STRING_71            ((HASHED_STRING_70 ^ _value[69]) * kStringPrime)
#define HASHED_STRING_72            ((HASHED_STRING_71 ^ _value[70]) * kStringPrime)
#define HASHED_STRING_73            ((HASHED_STRING_72 ^ _value[71]) * kStringPrime)
#define HASHED_STRING_74            ((HASHED_STRING_73 ^ _value[72]) * kStringPrime)
#define HASHED_STRING_75            ((HASHED_STRING_74 ^ _value[73]) * kStringPrime)
#define HASHED_STRING_76            ((HASHED_STRING_75 ^ _value[74]) * kStringPrime)
#define HASHED_STRING_77            ((HASHED_STRING_76 ^ _value[75]) * kStringPrime)
#define HASHED_STRING_78            ((HASHED_STRING_77 ^ _value[76]) * kStringPrime)
#define HASHED_STRING_79            ((HASHED_STRING_78 ^ _value[77]) * kStringPrime)
#define HASHED_STRING_80            ((HASHED_STRING_79 ^ _value[78]) * kStringPrime)
#define HASHED_STRING_81            ((HASHED_STRING_80 ^ _value[79]) * kStringPrime)
#define HASHED_STRING_82            ((HASHED_STRING_81 ^ _value[80]) * kStringPrime)
#define HASHED_STRING_83            ((HASHED_STRING_82 ^ _value[81]) * kStringPrime)
#define HASHED_STRING_84            ((HASHED_STRING_83 ^ _value[82]) * kStringPrime)
#define HASHED_STRING_85            ((HASHED_STRING_84 ^ _value[83]) * kStringPrime)
#define HASHED_STRING_86            ((HASHED_STRING_85 ^ _value[84]) * kStringPrime)
#define HASHED_STRING_87            ((HASHED_STRING_86 ^ _value[85]) * kStringPrime)
#define HASHED_STRING_88            ((HASHED_STRING_87 ^ _value[86]) * kStringPrime)
#define HASHED_STRING_89            ((HASHED_STRING_88 ^ _value[87]) * kStringPrime)
#define HASHED_STRING_90            ((HASHED_STRING_89 ^ _value[88]) * kStringPrime)
#define HASHED_STRING_91            ((HASHED_STRING_90 ^ _value[89]) * kStringPrime)
#define HASHED_STRING_92            ((HASHED_STRING_91 ^ _value[90]) * kStringPrime)
#define HASHED_STRING_93            ((HASHED_STRING_92 ^ _value[91]) * kStringPrime)
#define HASHED_STRING_94            ((HASHED_STRING_93 ^ _value[92]) * kStringPrime)
#define HASHED_STRING_95            ((HASHED_STRING_94 ^ _value[93]) * kStringPrime)
#define HASHED_STRING_96            ((HASHED_STRING_95 ^ _value[94]) * kStringPrime)
#define HASHED_STRING_97            ((HASHED_STRING_96 ^ _value[95]) * kStringPrime)
#define HASHED_STRING_98            ((HASHED_STRING_97 ^ _value[96]) * kStringPrime)
#define HASHED_STRING_99            ((HASHED_STRING_98 ^ _value[97]) * kStringPrime)
#define HASHED_STRING_100            ((HASHED_STRING_99 ^ _value[98]) * kStringPrime)
#define HASHED_STRING_101            ((HASHED_STRING_100 ^ _value[99]) * kStringPrime)
#define HASHED_STRING_102            ((HASHED_STRING_101 ^ _value[100]) * kStringPrime)
#define HASHED_STRING_103            ((HASHED_STRING_102 ^ _value[101]) * kStringPrime)
#define HASHED_STRING_104            ((HASHED_STRING_103 ^ _value[102]) * kStringPrime)
#define HASHED_STRING_105            ((HASHED_STRING_104 ^ _value[103]) * kStringPrime)
#define HASHED_STRING_106            ((HASHED_STRING_105 ^ _value[104]) * kStringPrime)
#define HASHED_STRING_107            ((HASHED_STRING_106 ^ _value[105]) * kStringPrime)
#define HASHED_STRING_108            ((HASHED_STRING_107 ^ _value[106]) * kStringPrime)
#define HASHED_STRING_109            ((HASHED_STRING_108 ^ _value[107]) * kStringPrime)
#define HASHED_STRING_110            ((HASHED_STRING_109 ^ _value[108]) * kStringPrime)
#define HASHED_STRING_111            ((HASHED_STRING_110 ^ _value[109]) * kStringPrime)
#define HASHED_STRING_112            ((HASHED_STRING_111 ^ _value[110]) * kStringPrime)
#define HASHED_STRING_113            ((HASHED_STRING_112 ^ _value[111]) * kStringPrime)
#define HASHED_STRING_114            ((HASHED_STRING_113 ^ _value[112]) * kStringPrime)
#define HASHED_STRING_115            ((HASHED_STRING_114 ^ _value[113]) * kStringPrime)
#define HASHED_STRING_116            ((HASHED_STRING_115 ^ _value[114]) * kStringPrime)
#define HASHED_STRING_117            ((HASHED_STRING_116 ^ _value[115]) * kStringPrime)
#define HASHED_STRING_118            ((HASHED_STRING_117 ^ _value[116]) * kStringPrime)
#define HASHED_STRING_119            ((HASHED_STRING_118 ^ _value[117]) * kStringPrime)
#define HASHED_STRING_120            ((HASHED_STRING_119 ^ _value[118]) * kStringPrime)
#define HASHED_STRING_121            ((HASHED_STRING_120 ^ _value[119]) * kStringPrime)
#define HASHED_STRING_122            ((HASHED_STRING_121 ^ _value[120]) * kStringPrime)
#define HASHED_STRING_123            ((HASHED_STRING_122 ^ _value[121]) * kStringPrime)
#define HASHED_STRING_124            ((HASHED_STRING_123 ^ _value[122]) * kStringPrime)
#define HASHED_STRING_125            ((HASHED_STRING_124 ^ _value[123]) * kStringPrime)
#define HASHED_STRING_126            ((HASHED_STRING_125 ^ _value[124]) * kStringPrime)
#define HASHED_STRING_127            ((HASHED_STRING_126 ^ _value[125]) * kStringPrime)
#define HASHED_STRING_128            ((HASHED_STRING_127 ^ _value[126]) * kStringPrime)
#define HASHED_STRING_129            ((HASHED_STRING_128 ^ _value[127]) * kStringPrime)


#define HASHED_STRING_SPECIALIZATION(n)                                                              \
template <>                                                                                         \
explicit HashedString(const char (&_value)[n]) : m_hash(DEMIGOAP_JOIN(HASHED_STRING_, n))  \
{                                                                                                   \
    m_value = _value;                                                                         \
}


HASHED_STRING_SPECIALIZATION(1)
HASHED_STRING_SPECIALIZATION(2)
HASHED_STRING_SPECIALIZATION(3)
HASHED_STRING_SPECIALIZATION(4)
HASHED_STRING_SPECIALIZATION(5)
HASHED_STRING_SPECIALIZATION(6)
HASHED_STRING_SPECIALIZATION(7)
HASHED_STRING_SPECIALIZATION(8)
HASHED_STRING_SPECIALIZATION(9)
HASHED_STRING_SPECIALIZATION(10)
HASHED_STRING_SPECIALIZATION(11)
HASHED_STRING_SPECIALIZATION(12)
HASHED_STRING_SPECIALIZATION(13)
HASHED_STRING_SPECIALIZATION(14)
HASHED_STRING_SPECIALIZATION(15)
HASHED_STRING_SPECIALIZATION(16)
HASHED_STRING_SPECIALIZATION(17)
HASHED_STRING_SPECIALIZATION(18)
HASHED_STRING_SPECIALIZATION(19)
HASHED_STRING_SPECIALIZATION(20)
HASHED_STRING_SPECIALIZATION(21)
HASHED_STRING_SPECIALIZATION(22)
HASHED_STRING_SPECIALIZATION(23)
HASHED_STRING_SPECIALIZATION(24)
HASHED_STRING_SPECIALIZATION(25)
HASHED_STRING_SPECIALIZATION(26)
HASHED_STRING_SPECIALIZATION(27)
HASHED_STRING_SPECIALIZATION(28)
HASHED_STRING_SPECIALIZATION(29)
HASHED_STRING_SPECIALIZATION(30)
HASHED_STRING_SPECIALIZATION(31)
HASHED_STRING_SPECIALIZATION(32)
HASHED_STRING_SPECIALIZATION(33)
HASHED_STRING_SPECIALIZATION(34)
HASHED_STRING_SPECIALIZATION(35)
HASHED_STRING_SPECIALIZATION(36)
HASHED_STRING_SPECIALIZATION(37)
HASHED_STRING_SPECIALIZATION(38)
HASHED_STRING_SPECIALIZATION(39)
HASHED_STRING_SPECIALIZATION(40)
HASHED_STRING_SPECIALIZATION(41)
HASHED_STRING_SPECIALIZATION(42)
HASHED_STRING_SPECIALIZATION(43)
HASHED_STRING_SPECIALIZATION(44)
HASHED_STRING_SPECIALIZATION(45)
HASHED_STRING_SPECIALIZATION(46)
HASHED_STRING_SPECIALIZATION(47)
HASHED_STRING_SPECIALIZATION(48)
HASHED_STRING_SPECIALIZATION(49)
HASHED_STRING_SPECIALIZATION(50)
HASHED_STRING_SPECIALIZATION(51)
HASHED_STRING_SPECIALIZATION(52)
HASHED_STRING_SPECIALIZATION(53)
HASHED_STRING_SPECIALIZATION(54)
HASHED_STRING_SPECIALIZATION(55)
HASHED_STRING_SPECIALIZATION(56)
HASHED_STRING_SPECIALIZATION(57)
HASHED_STRING_SPECIALIZATION(58)
HASHED_STRING_SPECIALIZATION(59)
HASHED_STRING_SPECIALIZATION(60)
HASHED_STRING_SPECIALIZATION(61)
HASHED_STRING_SPECIALIZATION(62)
HASHED_STRING_SPECIALIZATION(63)
HASHED_STRING_SPECIALIZATION(64)
HASHED_STRING_SPECIALIZATION(65)
HASHED_STRING_SPECIALIZATION(66)
HASHED_STRING_SPECIALIZATION(67)
HASHED_STRING_SPECIALIZATION(68)
HASHED_STRING_SPECIALIZATION(69)
HASHED_STRING_SPECIALIZATION(70)
HASHED_STRING_SPECIALIZATION(71)
HASHED_STRING_SPECIALIZATION(72)
HASHED_STRING_SPECIALIZATION(73)
HASHED_STRING_SPECIALIZATION(74)
HASHED_STRING_SPECIALIZATION(75)
HASHED_STRING_SPECIALIZATION(76)
HASHED_STRING_SPECIALIZATION(77)
HASHED_STRING_SPECIALIZATION(78)
HASHED_STRING_SPECIALIZATION(79)
HASHED_STRING_SPECIALIZATION(80)
HASHED_STRING_SPECIALIZATION(81)
HASHED_STRING_SPECIALIZATION(82)
HASHED_STRING_SPECIALIZATION(83)
HASHED_STRING_SPECIALIZATION(84)
HASHED_STRING_SPECIALIZATION(85)
HASHED_STRING_SPECIALIZATION(86)
HASHED_STRING_SPECIALIZATION(87)
HASHED_STRING_SPECIALIZATION(88)
HASHED_STRING_SPECIALIZATION(89)
HASHED_STRING_SPECIALIZATION(90)
HASHED_STRING_SPECIALIZATION(91)
HASHED_STRING_SPECIALIZATION(92)
HASHED_STRING_SPECIALIZATION(93)
HASHED_STRING_SPECIALIZATION(94)
HASHED_STRING_SPECIALIZATION(95)
HASHED_STRING_SPECIALIZATION(96)
HASHED_STRING_SPECIALIZATION(97)
HASHED_STRING_SPECIALIZATION(98)
HASHED_STRING_SPECIALIZATION(99)
HASHED_STRING_SPECIALIZATION(100)
HASHED_STRING_SPECIALIZATION(101)
HASHED_STRING_SPECIALIZATION(102)
HASHED_STRING_SPECIALIZATION(103)
HASHED_STRING_SPECIALIZATION(104)
HASHED_STRING_SPECIALIZATION(105)
HASHED_STRING_SPECIALIZATION(106)
HASHED_STRING_SPECIALIZATION(107)
HASHED_STRING_SPECIALIZATION(108)
HASHED_STRING_SPECIALIZATION(109)
HASHED_STRING_SPECIALIZATION(110)
HASHED_STRING_SPECIALIZATION(111)
HASHED_STRING_SPECIALIZATION(112)
HASHED_STRING_SPECIALIZATION(113)
HASHED_STRING_SPECIALIZATION(114)
HASHED_STRING_SPECIALIZATION(115)
HASHED_STRING_SPECIALIZATION(116)
HASHED_STRING_SPECIALIZATION(117)
HASHED_STRING_SPECIALIZATION(118)
HASHED_STRING_SPECIALIZATION(119)
HASHED_STRING_SPECIALIZATION(120)
HASHED_STRING_SPECIALIZATION(121)
HASHED_STRING_SPECIALIZATION(122)
HASHED_STRING_SPECIALIZATION(123)
HASHED_STRING_SPECIALIZATION(124)
HASHED_STRING_SPECIALIZATION(125)
HASHED_STRING_SPECIALIZATION(126)
HASHED_STRING_SPECIALIZATION(127)
HASHED_STRING_SPECIALIZATION(128)
HASHED_STRING_SPECIALIZATION(129)
};


DEMIGOAP_NAMESPACE_END
