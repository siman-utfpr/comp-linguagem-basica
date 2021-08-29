#!/bin/bash
echo "INICIANDO EXECUÇÃO"
NUMBEROFFILES=$(ls "./entrada" | wc -l)
CURRENTINDEX=1
for INPUTFILE in "./entrada"/* 
do 
  echo ""
  echo "ARQUIVO $CURRENTINDEX DE $NUMBEROFFILES"

  CURRENTINDEX=$((CURRENTINDEX+1))
  OUTPUTFILE="./saida/${INPUTFILE#*./entrada/}"

  echo "EXECUTANDO..."
  ./linguagem-basica "$INPUTFILE" "$OUTPUTFILE" &>./error_log

done 
echo ""
echo "PROCESSO CONCLUÍDO! OS ARQUIVOS DE SAÍDA ESTÃO EM ./saida/"