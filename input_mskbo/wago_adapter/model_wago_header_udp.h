#ifndef MODEL_WAGO_HEADER_UDP__HH
#define MODEL_WAGO_HEADER_UDP__HH

//#include "stdafx.h"
//#include "windows.h"

#include <stdint.h>

//#define DWORD unsigned int
//#define WORD unsigned short

#pragma pack(push, 1)

//=====================================================================================================================

// Цифровые выходные данные Кабины : УСО-WAGO ==> БРЭО-МСКБО

// ПУ ПКВ (САУ) - кнопки-лампы
union TFD_OutD_PU_PKV
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  ap         :  1;  //    1   - АП
		DWORD  mal_skor   :  1;  //    2   - МАЛ СКОР
		DWORD  avt_upr    :  1;  //    3   - АВТ УПР
		DWORD  goriz      :  1;  //    4   - ГОРИЗ
		DWORD  h_bar      :  1;  //    5   - H бар
		DWORD  posad      :  1;  //    6   - ПОСАД
		DWORD  dir_upr    :  1;  //    7   - ДИР УПР
		DWORD  visen      :  1;  //    8   - ВИСЕН
		DWORD  v_pr       :  1;  //    9   - V пр
		DWORD  marshr     :  1;  //   10   - МАРШР
		DWORD  avt_trim   :  1;  //   11   - АВТ ТРИМ
		DWORD  dovor      :  1;  //   12   - ДОВОР
		DWORD  ugl_skor   :  1;  //   13   - УГЛ СКОР
		DWORD  zakhod     :  1;  //   14   - ЗАХОД
		DWORD  mvp        :  1;  //   15   - МВП
		DWORD  pg         :  1;  //   16   - ПГ
		DWORD  ugol       :  1;  //   17   - УГОЛ
		DWORD  parir      :  1;  //   18   - ПАРИР
		DWORD  h_rv       :  1;  //   19   - H рв
		DWORD  res3220    : 13;  // 32..17 - резерв
	};
};

// РЦШ (РУС) - Левая (Правая)
union TFD_OutD_RCSH
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  rs         :  1;  //    1   - РС ЛЛ
		DWORD  vykl_ap    :  1;  //    2   - Выкл АП ЛЛ
		DWORD  trimmer    :  1;  //    3   - Триммер ЛЛ
		DWORD  spu        :  1;  //    4   - СПУ ЛЛ
		DWORD  rad        :  1;  //    5   - РАД ЛЛ
		DWORD  tormoz     :  1;  //    6   - Тормоз - только на левой РЦШ
		DWORD  res3207    : 26;  // 32..07 - резерв
	};
};

// Педали
union TFD_OutD_Pedals
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  L_1     :  1;  //    1   - Педаль левая ЛЛ (левого лётчика)
		DWORD  R_1     :  1;  //    2   - Педаль правая ЛЛ (левого лётчика)
		DWORD  L_2     :  1;  //    3   - Педаль левая ПЛ (правого лётчика)
		DWORD  R_2     :  1;  //    4   - Педаль правая ПЛ (правого лётчика)
		DWORD  res3205 : 28;  // 32..05 - резерв
	};
};

// РОШ (РУДы) левый + правый
union TFD_OutD_ROSH
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  upr_prozh_ll_vverkh :  1;  //    1   - Упр. прож. ЛЛ вверх
		DWORD  upr_prozh_ll_vniz   :  1;  //    2   - Упр. прож. ЛЛ вниз
		DWORD  upr_prozh_ll_vpravo :  1;  //    3   - Упр. прож. ЛЛ вправо
		DWORD  upr_prozh_ll_vlevo  :  1;  //    4   - Упр. прож. ЛЛ влево
		DWORD  friktsion_ll        :  1;  //    5   - Фрикцион ЛЛ
		DWORD  avar_sbros          :  1;  //    6   - Авар.сброс
		DWORD  takt_sbros          :  1;  //    7   - Такт.сброс
		DWORD  upr_prozh_pl_vverkh :  1;  //    8   - Упр. прож. ПЛ вверх
		DWORD  upr_prozh_pl_vniz   :  1;  //    9   - Упр. прож. ПЛ вниз
		DWORD  upr_prozh_pl_vpravo :  1;  //   10   - Упр. прож. ПЛ вправо
		DWORD  upr_prozh_pl_vlevo  :  1;  //   11   - Упр. прож. ПЛ влево
		DWORD  friktsion_pl        :  1;  //   12   - Фрикцион ПЛ
		DWORD  res3213             : 20;  // 32..13 - резерв
	};
};

// ЛБПЭП - левая боковая панель электропульта
union TFD_OutD_LeftSideCons
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  postoyan     :  1;  //    1 - Постоян.
		DWORD  ciklic       :  1;  //    2 - Цикл
		DWORD  kontur       :  1;  //    3 - Контур
		DWORD  ano_100      :  1;  //    4 - АНО 100%
		DWORD  ano_10       :  1;  //    5 - АНО 10%
		DWORD  mayak_yarko  :  1;  //    6 - Маяк ярко
		DWORD  den          :  1;  //    7 - День
		DWORD  noch         :  1;  //    8 - Ночь
		DWORD  res3209      : 24;  // 32..09 - резерв
	};
};

// Боковая ручка летчика (Stick)
union TFD_OutD_Stick
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  btn_1    :  1;  //    1   - Стик 1 ЛЛ
		DWORD  btn_2    :  1;  //    2   - Стик 2 ЛЛ
		DWORD  btn_3    :  1;  //    3   - Стик 3 ЛЛ
		DWORD  btn_Red 	:  1;  //    4   - Стик красн. ЛЛ
		DWORD  res3205  : 28;  // 32..05 - резерв
	};
};

// ЦП - центральный пульт
union TFD_OutD_CentrCons
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  radiomolchanie      :  1;  //    1   - Радиомолчание
		DWORD  vybor_oruzhiya      :  1;  //    2   - Выбор  оружия
		DWORD  privyazka           :  1;  //    3   - Привязка
		DWORD  kontrol_sas         :  1;  //    4   - Контроль САС
		DWORD  avar_sbros          :  1;  //    5   - Авар сброс
		DWORD  sbros_zadaniya      :  1;  //    6   - Сброс задания
		DWORD  obor_bol_mensh      :  1;  //    7   - Обор. Больше/Меньше
		DWORD  stoyanochny_tormoz  :  1;  //    8   - Стояночный тормоз
		DWORD  zapros              :  1;  //    9   - Запрос
		DWORD  uv                  :  1;  //   10   - УВ
		DWORD  tsu                 :  1;  //   11   - ЦУ
		DWORD  intertseptor_vypusk :  1;  //   12   - Интерцептор выпуск
		DWORD  intertseptor_uborka :  1;  //   13   - Интерцептор уборка
		DWORD  asp_1               :  1;  //   14   - АСП 1
		DWORD  asp_2               :  1;  //   15   - АСП 2
		DWORD  asp_3               :  1;  //   16   - АСП 3
		DWORD  asp_4               :  1;  //   17   - АСП 4
		DWORD  res3218             : 15;  // 32..18 - резерв
	};
};

// ППД - правая приборная доска
union TFD_OutD_RightInstrPan
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  radio          :  1;  //    1   - Радио ПЛ
		DWORD  fary           :  1;  //    2   - Фары ПЛ
		DWORD  shassi_vypusk  :  1;  //    3   - Шасси выпуск
		DWORD  shassi_uborka  :  1;  //    4   - Шасси уборка
		DWORD  res3205        : 28;  // 32..05 - резерв
	};
};
	
// ЛПД - левая приборная доска
union TFD_OutD_LeftInstrPan
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  suo        :  1;  //    1   - СУО
		DWORD  radio      :  1;  //    2   - Радио ЛЛ
		DWORD  fary       :  1;  //    3   - Фары ЛЛ
		DWORD  zapusk     :  1;  //    4   - Запуск
		DWORD  res3205    : 28;  // 32..05 - резерв
	};
};

// ЛПЭП - левая панель электропульта
union TFD_OutD_LeftOvrHeadCons
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  signal                   :  1;  //    1   - tumbler_1
		DWORD  prav_dvig_ruchn          :  1;  //    2   - tumbler_4_up
		DWORD  lev_dvig_ruchn           :  1;  //    3   - tumbler_3_up
		DWORD  baki_1_2                 :  1;  //    4   - tumbler_8
		DWORD  podves_baki              :  1;  //    5   - tumbler_7
		DWORD  toplivny_nasos_prav_dvig :  1;  //    6   - tumbler_6
		DWORD  toplivny_nasos_lev_dvig  :  1;  //    7   - tumbler_5
		DWORD  prav_dvig_vykl           :  1;  //    8   - tumbler_4_down
		DWORD  lev_dvig_vykl            :  1;  //    9   - tumbler_3_down
		DWORD  nv_rv                    :  1;  //   10   - tumbler_2
		DWORD  res3211                  : 22;  // 32..11 - резерв
	};
};

// ППЭП - правая панель электропульта
union TFD_OutD_RightOvrHeadCons
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  set_na_akkumulyator    :  1;    // 0 - Сеть на аккум.
		DWORD  aerodromnoe_pitanie    :  1;    // 1 - Аэродромное питание
		DWORD  generator_lev          :  1;    // 2 - Генератор левый
		DWORD  generator_prav         :  1;    // 3 - Генератор правый
		DWORD  akkumulyator_lev       :  1;    // 4 - Аккумулятор левый
		DWORD  akkumulyator_prav      :  1;    // 5 - Аккумулятор правый
		DWORD  preobrazovatel_avt     :  1;    // 6 - Преобразователь авт.
		DWORD  preobrazovatel_ruchn   :  1;    // 7 - Преобразователь ручн.
		DWORD  stg                    :  1;    // 8 - СТГ
		DWORD  tlg_tlf                :  1;    // 9 - ТЛГ/ТЛФ
		DWORD  komp_ant               :  1;    // 10 - КОМП/АНТ
		DWORD  freq3_incr             :  1;    // 11 - Част3+
		DWORD  freq3_decr             :  1;    // 12 - Част3-
		DWORD  freq2_incr             :  1;    // 13 - Част2+
		DWORD  freq2_decr             :  1;    // 14 - Част2-
		DWORD  freq1_incr             :  1;    // 15 - Част1+
		DWORD  freq1_decr             :  1;    // 16 - Част1-
		DWORD  kontr                  :  1;    // 17 - КОНТР
		DWORD  zap                    :  1;    // 18 - ЗАП
		DWORD  res3211                : 13;  // 32..20 - резерв
	};
};

// ПЩЭП - правый щиток электропульта
union TFD_OutD_RightTriangPan
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  obogrev        :  1;    // 1 - Обогрев
		DWORD  rezerv2_pschep :  1;    // 2 - Резерв2 ПЩЭП
		DWORD  res3203        : 30;  // 32..03 - резерв
	};
};

// ЛЩЭП - левый щиток электропульта
union TFD_OutD_LeftTriangPan
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  obogrev_svvd   :  1;    // 1 - Обогрев СВВД
		DWORD  rezerv_lschep  :  1;    // 2 - Резерв ЛЩЭП
		DWORD  res3203        : 30;  // 32..03 - резерв
	};
};

// ЛПАЗС
union TFD_OutD_LeftCircBreakCons
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  breo            :  1;    //  1 - БРЭО                (АЗС  1)
		DWORD  npk             :  1;    //  2 - НПК                 (АЗС  2)
		DWORD  rv              :  1;    //  3 - РВ                  (АЗС  3)
		DWORD  diss            :  1;    //  4 - ДИСС                (АЗС  4)
		DWORD  ark             :  1;    //  5 - АРК                 (АЗС  5)
		DWORD  ins_1           :  1;    //  6 - ИНС-1               (АЗС  6)
		DWORD  ins_2           :  1;    //  7 - ИНС-2               (АЗС  7)
		DWORD  suo             :  1;    //  8 - СУО                 (АЗС  8)
		DWORD  ppu             :  1;    //  9 - ППУ                 (АЗС  9)
		DWORD  privod_ppu      :  1;    // 10 - Привод ППУ          (АЗС 10)
		DWORD  tpsl            :  1;    // 11 - ТпСЛ                (АЗС 11)
		DWORD  sro             :  1;    // 12 - СРО                 (АЗС 12)
		DWORD  srz             :  1;    // 13 - СРЗ                 (АЗС 13)
		DWORD  bko             :  1;    // 14 - БКО                 (АЗС 14)
		DWORD  rlsu            :  1;    // 15 - РЛСУ                (АЗС 15)
		DWORD  as_bpla         :  1;    // 16 - АС БПЛА             (АЗС 16)
		DWORD  rls             :  1;    // 17 - РЛС                 (АЗС 17)
		DWORD  ops             :  1;    // 18 - ОПС                 (АЗС 18)
		DWORD  tsims_ukv_1     :  1;    // 19 - ЦИМС УКВ-1          (АЗС 19)
		DWORD  radio           :  1;    // 20 - РАДИО               (АЗС 20)
		DWORD  kss             :  1;    // 21 - КСС                 (АЗС 21)
		DWORD  ag              :  1;    // 22 - АГ                  (АЗС 22)
		DWORD  onv             :  1;    // 23 - ОНВ                 (АЗС 23)
		DWORD  registr         :  1;    // 24 - Регистр.            (АЗС 24)
		DWORD  inpr            :  1;    // 25 - ИНПР                (АЗС 25)
		DWORD  avar_podyem_ppu :  1;    // 26 - Авар. подъём ППУ    (АЗС 26)
		DWORD  sppz_rabota     :  1;    // 27 - СППЗ Работа         (АЗС 27)
		DWORD  sbkv            :  1;    // 28 - СБКВ                (АЗС 28)
		DWORD  res3229			   :  4;  // 32..29 - резерв
	};
};

// ПУ КАИ - Надстройка (Левая часть панели автопилота)
union TFD_OutD_KAI_Ctrl
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  ruch     :  1;  //    1   - Руч.
		DWORD  setka    :  1;  //    2   - Сетка
		DWORD  den      :  1;  //    3   - День
		DWORD  test     :  1;  //    4   - Тест
		DWORD  res3229  : 28;  // 32..05 - резерв
	};
};

//---------------------------------------------------------------------------------------------------------------------

// Цифровые выходные данные Кабины : УСО-WAGO ==> БРЭО-МСКБО
struct TFD_OutDig
{
	TFD_OutD_RCSH									RCSH_1;							// РЦШ (РУС) - Левая
	TFD_OutD_RCSH									RCSH_2;							// РЦШ (РУС) - Правая
	TFD_OutD_Pedals								pedals;							// Педали
	TFD_OutD_ROSH									ROSH;								// Левый и правый рычаги «шаг-газ» (ШГ) == РОШ (Рычаг общего шага)
	TFD_OutD_LeftSideCons					leftSideCons;				// ЛБПЭП - левая боковая панель электропульта
	TFD_OutD_Stick								stick_1;						// Боковая ручка летчика - Левого
	TFD_OutD_Stick								stick_2;						// Боковая ручка летчика - Правого
	TFD_OutD_CentrCons						centrCons;					// ЦП - центральный пульт 
	TFD_OutD_RightInstrPan				rightInstrPan;			// ППД - правая приборная доска
	TFD_OutD_LeftInstrPan					leftInstrPan;				// ЛПД - левая приборная доска
	TFD_OutD_LeftOvrHeadCons			leftOvrHeadCons;		// ЛПЭП - левая панель электропульта [Left Overhead Console]
	TFD_OutD_RightOvrHeadCons			rightOvrHeadCons;		// ППЭП - правая панель электропульта
	TFD_OutD_RightTriangPan				rightTriPan;				// ПЩЭП - правый щиток электропульта
	TFD_OutD_LeftTriangPan				leftTriPan;					// ЛЩЭП - левый щиток электропульта
	TFD_OutD_LeftCircBreakCons		leftCircBreakCons;	// ЛПАЗС [Left Circuit Breaker Console]
	TFD_OutD_KAI_Ctrl							ctrlKAI;						// ПУ КАИ - Надстройка (Левая часть панели автопилота)
	TFD_OutD_PU_PKV								btnPUPKV;						// ПУ ПКВ (САУ) - кнопки-лампы
};


//=====================================================================================================================

// ЛПД - левая приборная доска
struct TFD_OutE_LeftInstrPan
{
	uint32_t  encoder_a;     	// Энкодер А (32-битный счётчик энкодера А)
};

// Счётчики энкодеров
struct TFD_OutE_Enc_data {
	TFD_OutE_LeftInstrPan  leftInstrPan;		// ЛПД - левая приборная доска
};

//=====================================================================================================================

// ППЭП - правая панель электропульта
struct TFD_InA_RightOvrHeadCons
{
	float ark_freq;     // Индикатор «Набор частоты» на пульте АРК 
};

// Выходные данные для цифровых индикаторов
struct TFD_InA_Indics
{
	TFD_InA_RightOvrHeadCons  aiRtOvrHdCons;		// ППЭП - правая панель электропульта
};

//=====================================================================================================================

// Цифровые входные данные Кабины : УСО-WAGO <== БРЭО-МСКБО

// ППД - правая приборная доска
union TFD_InD_RightInstrPan
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  shassi           :  1;  // 1 - Шасси индикатор
		DWORD  res3202          : 31;  // 32..05 - резерв
	};
};

// ЛЩЭП - левый щиток электропульта
union TFD_InD_LeftTriPan
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  obogrev_svvd_ispraven 	:  1;  // 1 - Обогр. СВВД испр.
		DWORD  res3202                : 31;  // 32..02 - резерв
	};
};

// ПЩЭП - правый щиток электропульта
union TFD_InD_RightTriPan
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  generator_otklyuchen 	:  1;  //    1 - Генератор выкл.
		DWORD  pzu_vklyuchen          :  1;  //    2 - ПЗУ включен
		DWORD  res3203                : 30;  // 32..03 - резерв
	};
};

// ЛПЭП - левая панель электропульта
union TFD_InD_LeftOvrHeadCons
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  vklyuchi_pos        	:  1;    //  1   - Включи ПОС
		DWORD  pos_vklyuchen       	:  1;    //  2   - ПОС включен
		DWORD  generator_vklyuchen 	:  1;    //  3   - Генератор включен
		DWORD  raskhod_baka        	:  1;    //  4   - Расход бака
		DWORD  baka_1              	:  1;    //  5   - Бака 1
		DWORD  baka_2              	:  1;    //  6   - Бака 2
		DWORD  res3207              : 26;  // 32..07 - резерв
	};
};

// ППЭП - правая панель электропульта
union TFD_InD_RightOvrHeadCons
{
	DWORD	   dw32;          // рр.32..01 - слово целиком
	struct{
		DWORD  otkaz_lev_akkum        :  1;  //    1 - Отказ лев. аккумулятора
		DWORD  otkaz_prav_akkum       :  1;  //    2 - Отказ прав. аккумулятора
		DWORD  otkaz_lev_generatora   :  1;  //    3 - Отказ лев. генератора.
		DWORD  otkaz_prav_generatora  :  1;  //    4 - Отказ прав. генератора.
		DWORD  rozetka_vklyuchena     :  1;  //    5 - Розетка включена
		DWORD  res3206                : 27;  // 32..06 - резерв
	};
};

//---------------------------------------------------------------------------------------------------------------------

// Цифровые входные данные Кабины : УСО-WAGO <== БРЭО-МСКБО
struct TFD_InDig
{
	TFD_InD_RightInstrPan			rightInstrPan;			// ППД  - правая приборная доска
	TFD_InD_LeftTriPan				leftTriPan;					// ЛЩЭП - левый щиток электропульта
	TFD_InD_RightTriPan				rightTriPan;				// ПЩЭП - правый щиток электропульта
	TFD_InD_LeftOvrHeadCons		leftOvrHeadCons;		// ЛПЭП - левая панель электропульта
	TFD_InD_RightOvrHeadCons	rightOvrHeadCons;		// ППЭП - правая панель электропульта
	TFD_OutD_PU_PKV						lmpPUPKV;
};

//=====================================================================================================================

// Аналоговые выходные данные Кабины : УСО-WAGO ==> БРЭО-МСКБО

// ДОС - датчики обратной связи органов управления
struct TFD_OutA_FltCtrl
{
	uint16_t  psi;       // Курс
	uint16_t  gam;       // Крен
	uint16_t  tng;       // Тангаж
	uint16_t  shv;       // Шаг винта
	uint16_t  gaz_1;     // Газ двиг.1
	uint16_t  gaz_2;     // Газ двиг.2
	uint16_t  rezerv[2];
};

// Боковая ручка летчика - Левого (Правого)
struct TFD_OutA_Stick
{
	uint16_t  MRK;       // МРК ЛЛ - механизм рулевого колеса
	uint16_t  gam;       // Стик крен
	uint16_t  tng;       // Стик тангаж
	uint16_t  knpUD;     // Стик кн. верх
	uint16_t  knpLR;     // Стик кн. лев.
	uint16_t  rezerv[3];
};

// ЦП - центральный пульт
struct TFD_OutA_CentCons
{
	uint16_t  zakr;      // Закрылки-аналог : (ao_norm :: 0°=65535 / 15°=43787 / 28°=24793 / 35°=13044 / 0°=00000)
	uint16_t  rezerv;
};

// ППЭП - правая панель электропульта
struct TFD_OutA_RightOvrHeadCons
{
	uint16_t  chan_ARK;  // ПУ АРК : Галетный переключатель каналов АРК
	uint16_t  rezerv;
};
    
// ПУ КАИ - Надстройка (Левая часть панели автопилота)
struct TFD_OutA_KAI
{
	uint16_t  brt_KAI;   // Ярк. КАИ
	uint16_t  rezerv;
};

//---------------------------------------------------------------------------------------------------------------------

// Аналоговые выходные данные Кабины : УСО-WAGO ==> БРЭО-МСКБО
struct TFD_OutA
{
	TFD_OutA_FltCtrl						aoFltCtrl;			// ДОС - датчики обратной связи органов управления [Feedback transducers]
	TFD_OutA_Stick							aoStick1;				// Боковая ручка летчика - Левого
	TFD_OutA_Stick							aoStick2;				// Боковая ручка летчика - Правого
	TFD_OutA_CentCons						aoCentCons;			// ЦП - центральный пульт
	TFD_OutA_RightOvrHeadCons		aoRtOvrHdCons;	// ППЭП - правая панель электропульта
	TFD_OutA_KAI								aoKAI;					// ПУ КАИ - Надстройка (Левая часть панели автопилота)
};

//=====================================================================================================================

// Управление моделью WAGO
struct TFD_InD_WAGO_Ctrl
{
	union
	{
		DWORD	   dw32;          // рр.32..01 - слово целиком
		struct{
			DWORD  connected_to_couplers  :  1;  // Управление соединением с каплерами WAGO. 1 - запрос на установку соединения, 0 - запрос разрыва соединения
			DWORD  window_visible					:  1;  // Управление окном приложения. 1 - окно видимо, 0 - окно скрыто.
			DWORD  res3203                : 30;  // 32..03 - резерв
		};
	};
	DWORD	   dw32_res[15];   //
};

// Состояние модели WAGO
struct TFD_OutD_WAGO_Sts
{
	union
	{
		DWORD	   dw32;          // рр.32..01 - слово целиком
		struct{
			DWORD  connect_sts  :  1;  //   01   - статус соединения с каплерами WAGO. 1 - соединение установлено, 0 - соединение отсутствует
			DWORD  res3202      : 31;  // 32..02 - резерв
		};
	};
	DWORD	   dw32_res[15];   //
};

//=====================================================================================================================
//=====================================================================================================================

// Входные данные Кабины : УСО-WAGO <== БРЭО-МСКБО :
struct TFD_WAGO_Inputs
{
	TNET_U16	idpack;								// [2] идентификатор пакета == 0x0061
	TNET_U16	szbuf;								// [2] размер буфера данных пакета [байт]
	TNET_U32	step;									// [4] шаг счета клиента
	//
	TFD_InDig			    do_bits;		// Цифровые входные данные Кабины : УСО-WAGO <== БРЭО-МСКБО
	TFD_InD_WAGO_Ctrl		wagoCtrl;		// Управление моделью WAGO
	TFD_InA_Indics			indics;			// Выходные данные для цифровых индикаторов
};


// Выходные данные Кабины : УСО-WAGO ==> БРЭО-МСКБО :
struct TFD_WAGO_Outputs
{
	TNET_U16	idpack;								// [2] идентификатор пакета == 0x0062
	TNET_U16	szbuf;								// [2] размер буфера данных пакета [байт]
	TNET_U32	step;									// [4] шаг счета клиента
	//
	TFD_OutDig					di_bits;		// Цифровые выходные данные Кабины : УСО-WAGO ==> БРЭО-МСКБО
	TFD_InDig						do_bits;		// Цифровые входные данные Кабины : УСО-WAGO <== БРЭО-МСКБО
	TFD_OutA						ao_code;		// Аналоговые выходные данные Кабины : УСО-WAGO ==> БРЭО-МСКБО
	TFD_OutA						ao_norm;
	TFD_InD_WAGO_Ctrl		wagoCtrl;		// Управление моделью WAGO
	TFD_OutD_WAGO_Sts		wagoSts;		// Состояние модели WAGO
	TFD_OutE_Enc_data		encData;		// Счётчики энкодеров
	TFD_InA_Indics			indics;			// Выходные данные для цифровых индикаторов
};

//=====================================================================================================================
//=====================================================================================================================

#pragma pack(pop)

#endif // MODEL_WAGO_HEADER_UDP__HH
