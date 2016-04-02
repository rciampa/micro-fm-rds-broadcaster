/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Richard Ciampa & Brandan Lockwood
 *
 * Created on April 1, 2016, 10:30 PM
 * 
 * Abstract: 
 */

/*
 * Includes in alpha order
 */

#include <curl/curl.h>
#include <jsmn/jsmn.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/*
 * Constants and macros
 */


/*
 * Function prototypes
 */

/*
 * 
 */
bool web_sevice_radio_data_fetch();

/*
 * 
 */
void update_rds_information();

/*
 *  
 */
bool set_fm_trans_freq();

struct {
    char freq[4]; //Four characters ONLY.
    char rds_id[25]; // RDS ID
    char rds_data[100];
    char program[30]; // The audio file to play
} radioData;


/*
 * 
 */
int main(int argc, char** argv) {

    CURLcode init_code;
    init_code = curl_global_init(CURL_GLOBAL_NOTHING);
    
    web_sevice_radio_data_fetch();

    return (EXIT_SUCCESS);
}

bool web_sevice_radio_data_fetch() {

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, "http://hosting.otterlabs.org/lockwoodbrandane/public_html/fm/micro-fm-webservice/mfm-service.php?method=getRadioInformation&format=json");
        res = curl_easy_perform(curl);

        if (CURLE_OK == res) {
            char *cont_type;
            
            /* Get the content from the web service */
            res = curl_easy_getinfo(curl, CURLINFO_DATA_OUT, &cont_type);

            if ((CURLE_OK == res) && cont_type){
                printf("%s", cont_type);
            }
        }

        //Cleanup
        curl_easy_cleanup(curl);
    }
    return true;
}

void update_rds_information() {

}

bool set_fm_trans_freq() {

    return true;
}

