/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "norm.hpp"

namespace CasADi{

Norm::Norm(const MX& x){
  setDependencies(x);
  setSparsity(CRSSparsity(1,1,true));
}

void Norm::evaluate(const VDptr& input, Dptr& output, const VVDptr& fwdSeed, VDptr& fwdSens, const VDptr& adjSeed, VVDptr& adjSens, int nfwd, int nadj){
  throw CasadiException("Norm::evaluate not implemented");
}

Norm2::Norm2(const MX& x) : Norm(x){
}

Norm2* Norm2::clone() const{
  return new Norm2(*this);
}

void Norm2::evaluate(const VDptr& input, Dptr& output, const VVDptr& fwdSeed, VDptr& fwdSens, const VDptr& adjSeed, VVDptr& adjSens, int nfwd, int nadj){
  if(nfwd==0 && nadj==0){
   double temp=0;
   for (int k=0;k<dep(0).size();k++) {
    temp+=input[0][k]*input[0][k];
   }
   output[0]=sqrt(temp);
   return; 
  }

  throw CasadiException("Norm2::evaluate not implemented");
}


void Norm2::print(std::ostream &stream, const std::vector<std::string>& args) const{
  stream << "||" << args.at(0) << "||_2"; 
}

Norm1::Norm1(const MX& x) : Norm(x){
}

Norm1* Norm1::clone() const{
  return new Norm1(*this);
}

void Norm1::print(std::ostream &stream, const std::vector<std::string>& args) const{
  stream << "||" << args.at(0) << "||_1"; 
}

void Norm1::evaluate(const VDptr& input, Dptr& output, const VVDptr& fwdSeed, VDptr& fwdSens, const VDptr& adjSeed, VVDptr& adjSens, int nfwd, int nadj){
  if(nfwd==0 && nadj==0){
   double temp=0;
   for (int k=0;k<dep(0).size();k++) temp+=std::abs(input[0][k]);
   output[0]=temp;
   return; 
  }

  throw CasadiException("Norm2::evaluate not implemented");
}

NormInf::NormInf(const MX& x) : Norm(x){
}

NormInf* NormInf::clone() const{
  return new NormInf(*this);
}

void NormInf::print(std::ostream &stream, const std::vector<std::string>& args) const{
  stream << "||" << args.at(0) << "||_inf"; 
}

void NormInf::evaluate(const VDptr& input, Dptr& output, const VVDptr& fwdSeed, VDptr& fwdSens, const VDptr& adjSeed, VVDptr& adjSens, int nfwd, int nadj){
  if(nfwd==0 && nadj==0){
   double temp=std::numeric_limits<double>::infinity();
   double a;
   for (int k=0;k<dep(0).size();k++) {
    a = std::abs(input[0][k]);
    if (a>temp) temp=a;
   }
   output[0]=temp;
   return; 
  }

  throw CasadiException("NormInf::evaluate not implemented");
}

} // namespace CasADi

