#!/bin/bash

# Fecha inicial
start_year=2015
end_year=$(date +"%Y")

# Tu clave de API
#api_key="eyJhbGciOiJIUzUxMiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE3NDgxMzI0NTAsInR5cGUiOiJleHRlcm5hbCIsInVzZXIiOiJ1bm9AeWFob28uY29tIn0.meWWPNP906rSL7wDv47mrZpT8LDDwlf9jQelWeo04y21ZlcWm_eiO71UMh_KFn7bmof2rvkmYlhiWfZ_OJ24Kg"
api_key="eyJhbGciOiJIUzUxMiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE3NDgxMzMxNzEsInR5cGUiOiJleHRlcm5hbCIsInVzZXIiOiJkb3NAeWFob28uY29tIn0.UhszpvycPIOmG9eDipEKnB_masjC6QEjVUKbpceU-P1cTmBw4TWup1FgRoTjWFr2cwePCl5yZhjcSL456-eOaA"

# API endpoint
api_url="https://api.estadisticasbcra.com/usd?s"

# Header de autorización
auth_header="Authorization: Bearer $api_key"

# Recorre los años y meses
for year in $(seq $start_year $end_year); do
  for month in $(seq -w 1 12); do
    # Fecha en formato YYYY-MM-DD
    date="${year}-${month}-03"

    # Realiza la solicitud a la API
    response=$(curl -s -H "$auth_header" "${api_url}")

    # Filtra los resultados para la fecha específica
    rate=$(echo "$response" | jq -r --arg date "$date" '.[] | select(.d == $date)')

    # Comprueba si la respuesta contiene datos
    if [[ -n "$rate" ]]; then
      # Extrae la cotización de compra y venta del JSON de la respuesta
      valor=$(echo "$rate" | jq -r '.v')
      echo "Fecha: $date, Valor: $valor"
    else
      echo "No hay datos disponibles para la fecha: $date"
    fi

    # Si llegamos al año actual y al mes actual, salimos del bucle
    if [[ "$year" == "$end_year" && "$month" == $(date +"%m") ]]; then
      break 2
    fi
  done
done
