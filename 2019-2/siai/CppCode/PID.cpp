#include "PID.h"

PID::PID(double posDesejada){
    this->kp = 0;
    this->ki = 0;
    this->kd = 0;
    this->dt = 0.01;
    this->integral = 0;
    this->maxPos = 1000;
    this->minPos = 0;
    this->preErro = 0;
    this->erro;
    this->posAtual = 0;
    this->termoProporcional = 0;
    this->termoIntegrativo = 0;
    this->termoDerivativo = 0;
    this->posDesejada = posDesejada;
}

void PID::movimenta(){
    int iteracao = 0;
    do{
        calculaPID();
        iteracao++;
    }while(abs(this->erro) > 0.0001 && iteracao < MAX_ITERACOES);
}

void PID::calculaPID(){
    calculaErro();
    calculaProporcional();
    calculaIntegrativo();
    calculaDerivativo();
    this->preErro = this->erro;
    double posSugerida = calculaPosicaoSugerida(); 
    calculaPosicaoFinal(posSugerida);
}

void PID::calculaErro(){
    this->erro = this->posDesejada-this->posAtual;
}

void PID::calculaProporcional(){
    this->termoProporcional =  this->kp * this->erro;
}

void PID::calculaIntegrativo(){
    this->integral += this->erro * this->dt;
    this->termoIntegrativo =  this->ki * this->integral;
}

void PID::calculaDerivativo(){
    double derivativo = (this->erro - this->preErro) / this->dt;
    this->termoDerivativo = this->kd * derivativo;
}

double PID::calculaPosicaoSugerida(){
    return termoProporcional + termoIntegrativo + termoDerivativo;
}

void PID::calculaPosicaoFinal(double posicaoSugerida){
    if(posicaoSugerida > this->maxPos)
        this->posAtual = this->maxPos;
    else if(posicaoSugerida < this->minPos)
        this->posAtual = this->minPos;
    else
        this->posAtual = posicaoSugerida;
}

double PID::getKp(){
    return this->kp;
}

double PID::getKi(){
    return this->ki;
}

double PID::getKd(){
    return this->kd;
}

void PID::setKp(double kp){
    this->kp = kp;
}

void PID::setKi(double ki){
    this->ki = ki;
}

void PID::setKd(double kd){
    this->kd = kd;
}