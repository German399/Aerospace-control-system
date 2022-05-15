#include<iostream>
#include"kbo.hxx"


void KBO::from_json()
{
KBO1.input.V = LAdata["V"];
KBO1.input.tet = LAdata["tet"];

return;
}

void KBO::to_json()
{
     KBOdata["tet"]= KBO1.output.INS.tet;
     KBOdata["tet"]= KBO1.output.SVS.Vprib;
return;
}

void KBO::integrate()
{
   KBO1.output.SVS.Vprib = KBO1.input.V*1.25 + 0.45;
   KBO1.output.INS.tet = KBO1.input.tet*10;

    //KBO.t_KBO = KBO.t_mskbo;
    ///здесь действия
    return;
}

void KBO::print()
{
    //KBO.t_KBO = KBO.t_mskbo;
    ///здесь действия
    return;
}

void KBO::update(){
    from_json();
    integrate();

    to_json();

}
