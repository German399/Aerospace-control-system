#ifndef GENERAL_DATA_MSKBO_H    // если имя GENERAL_DATA_MSKBO_H  ещё не определено
#define GENERAL_DATA_MSKBO_H   // определить имя GENERAL_DATA_MSKBO_H  
struct tdata{
            //входные данные
            //данные от ИУП - джойстиков и других органов управления
    struct Joi{
    double X,
           Y,
           Z,
           Xrot,
           Yrot,
           Zrot;
	bool Btn[100];
    };
            //входные данные от САУ 
    struct tSAU{
    double tetZ, 
           gamZ, 
           psiZ, 
           Vzad,
           VzadMax;
    };
            //внешняя среда
           ///общий глобальный таймер стенда моделирования Добавить
    struct model_external{
        double
           t_mskbo, 
           We, 
           Wn, 
           gN, 
           gE, 
           gH;
    };
            //входные/выходные данные(на первом шаге входными являются данные инициализации, начальные условия/позиция)
     struct tLA{
         double
           t_la,
            ///Широта 
           lat,
            ///Долгота    
           lon,
           H,
           psi, 
           tet, 
           gam,
           Upsi, 
           Ugam,
           Utet,
           V,
           Ve,
           Vn,
           Vh,
           ax,
           ay,
           az,
           ny,
           nymax;
     };
         struct tKBO{
         double
           t_kbo,
            ///Широта 
           lat,
            ///Долгота    
           lon,
           H,
           psi, 
           tet, 
           gam,
           Upsi, 
           Ugam,
           Utet,
           V,
           Ve,
           Vn,
           Vh,
           ax,
           ay,
           az,
           ny,
           nymax;
     };       

};//распакованная структура данных, для её создания из джсон надо вызвать метод from_json(), а после интегрирования упаковать назад при помощи to_json()
#endif//GENERAL_DATA_MSKBO_H  если  имя CPPSTUDIO_H уже определено, повторно не определять