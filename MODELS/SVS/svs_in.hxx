/*****************************************************************************/
/*                       ЗАГОЛОВОЧНЫЙ ФАЙЛ МОДЕЛИ СВС                        */
/*                            ВХОДНЫЕ ПАРАМЕТРЫ                              */
/*                                                                           */
/*****************************************************************************/
#ifndef SVS_IN_HXX
#define SVS_IN_HXX

// Структура входных параметров СВС
struct TSVS_IN
{
    // Количество тиков от диспетчера комплекса [ед]
    unsigned long tick;

    // Вес одного тика [мс]
    unsigned long dt;

    // Разрешение запуска основного цикла от диспетчера
    short go;

    /*Ниже необходимо написать свой код - наполнение входной структуры*/
    
    // Скорость ЛА [м/с]
    float V;

    // Высота абсолютная [м]
    float H;

    // Ускорение свободного падения [м/с/c]
    float g;

    // Скорость ветра [м/с]
    float W;

    // Курс ветра [м/с]
    float psi_W;

    // Температура воздуха на высоте
	float T_atmo;

	// Давление воздуха на высоте H и широте phi [Па]
	float P_atmo;

	// Плотность воздуха на высоте H и широте phi [кг/м^3]
	float rho_atmo;

    /*Конец пользовательского кода*/
};

extern TSVS_IN SVS_in;


#endif