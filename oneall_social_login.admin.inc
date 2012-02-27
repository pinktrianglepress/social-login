<?php
/**
 * @package   	OneAll Social Login Admin
 * @copyright 	Copyright 2012 http://www.oneall.com - All rights reserved.
 * @license   	GNU/GPL 2 or later
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,USA.
 *
 * The "GNU General Public License" (GPL) is available at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 *
 */

/**
 * @file
 * Contains the administration are interface for the Oneall Social Login Module.
 * The user may chose where to display the module and setup it's behavior.
 */

/**
 * Displays the settings page
 */
function oneall_social_login_admin_settings($form, &$form_state) {

  //Include the list of providers

  require_once 'oneall_social_login.providers.php';

  //Static - Used to display the provider icons
  drupal_add_css(drupal_get_path('module', 'oneall_social_login') . '/oneall_social_login.admin.css');

  //Read Settings
  $settings = oneall_social_login_admin_get_settings();

  //API Settings
  $form ['oneall_social_login_api'] = array(
    '#type' => 'fieldset',
    '#title' => t('API Settings'),
    '#description' => t('<a href="@setup_oneall_social_login" target="_blank">Click here to create and view your API Credentials</a>', array(
      '@setup_oneall_social_login' => 'https://app.oneall.com/applications/'
    ))
  );

  //API Subdomain
  $form ['oneall_social_login_api'] ['api_subdomain'] = array(
    '#id' => 'api_subdomain',
    '#type' => 'textfield',
    '#title' => t('API Subdomain:'),
    '#default_value' => (!empty($settings ['api_subdomain']) ? $settings ['api_subdomain'] : ''),
    '#size' => 60,
    '#maxlength' => 60,
  );

  //API Public Key
  $form ['oneall_social_login_api'] ['api_key'] = array(
    '#id' => 'api_key',
    '#type' => 'textfield',
    '#title' => t('API Public Key:'),
    '#default_value' => (!empty($settings ['api_key']) ? $settings ['api_key'] : ''),
    '#size' => 60,
    '#maxlength' => 60,
  );

  //API Private Key
  $form ['oneall_social_login_api'] ['api_secret'] = array(
    '#id' => 'api_secret',
    '#type' => 'textfield',
    '#title' => t('API Private Key:'),
    '#default_value' => (!empty($settings ['api_secret']) ? $settings ['api_secret'] : ''),
    '#size' => 60,
    '#maxlength' => 60,
  );

  //API Verify Settings Button
  $form ['oneall_social_login_api'] ['oneall_social_login_verify'] = array(
    '#id' => 'oneall_social_login_check_api_button',
    '#type' => 'button',
    '#value' => t('Verify API Settings'),
    '#weight' => 1,
    '#ajax' => array(
      'callback' => 'oneall_social_login_admin_ajax_check_api_connection_callback',
      'wrapper' => 'oneall_social_login_check_api_result',
      'method' => 'replace'
    ),
  );

  //API Verify Settings Result
  $form ['oneall_social_login_api'] ['oneall_social_login_check_api_result'] = array(
    '#prefix' => '<div id="oneall_social_login_check_api_result">',
    '#suffix' => '</div>'
  );

  //Settings
  $form ['oneall_social_login_settings_side_pannel'] = array(
    '#type' => 'fieldset',
    '#title' => t('Side Pannel Settings')
  );

  $form ['oneall_social_login_settings_side_pannel'] ['side_pannel_icons'] = array(
    '#type' => 'select',
    '#title' => t('Social Login Icons'),
    '#description' => t('Allows the users to login/register with their social network account, or with their already existing account.'),
    '#options' => array(
      'above' => t('Show the Social Login icons above the existing login form'),
      'below' => t('Show the Social Login icons below the existing login form (Default, recommended)'),
      'disable' => t('Do not show the Social Login icons the side pannel')
    ),
    '#default_value' => (empty($settings ['side_pannel_icons']) ? 'above' : $settings ['side_pannel_icons'])
  );

  $form ['oneall_social_login_settings_side_pannel'] ['side_pannel_caption'] = array(
    '#type' => 'textfield',
    '#title' => t('Social Login Icons: Caption [Leave empty for none]'),
    '#default_value' => (!isset($settings ['side_pannel_caption']) ? t('Register/Login with:') : $settings ['side_pannel_caption']),
    '#size' => 60,
    '#maxlength' => 60,
    '#description' => t('This is the title displayed above the social network icons.')
  );

  $form ['oneall_social_login_settings_login_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login Page Settings')
  );

  $form ['oneall_social_login_settings_login_page'] ['login_page_icons'] = array(
    '#type' => 'select',
    '#title' => t('Social Login Icons'),
    '#description' => t('Allows the users to login with their social network account, or with their already existing account.'),
    '#options' => array(
      'above' => t('Show the Social Login icons above the existing login form'),
      'below' => t('Show the Social Login icons below the existing login form (Default, recommended)'),
      'disable' => t('Do not show the Social Login icons on the login page')
    ),
    '#default_value' => (empty($settings ['login_page_icons']) ? 'above' : $settings ['login_page_icons'])
  );

  $form ['oneall_social_login_settings_login_page'] ['login_page_caption'] = array(
    '#type' => 'textfield',
    '#title' => t('Social Login Icons: Caption [Leave empty for none]'),
    '#default_value' => (!isset($settings ['login_page_caption']) ? t('Login with:') : $settings ['login_page_caption']),
    '#size' => 60,
    '#maxlength' => 60,
    '#description' => t('This is the title displayed above the social network icons.')
  );

  $form ['oneall_social_login_settings_registration_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Registration Page Settings'),
  );

  $form ['oneall_social_login_settings_registration_page'] ['registration_page_icons'] = array(
    '#type' => 'select',
    '#title' => t('Social Login Icons'),
    '#description' => t('Allows the users to register by using their social network account, or by creating a regular account.'),
    '#options' => array(
      'above' => t('Show the Social Login icons above the existing login form (Default, recommended)'),
      'below' => t('Show the Social Login icons below the existing login form'),
      'disable' => t('Do not show the Social Login icons on the registration page')
    ),
    '#default_value' => (empty($settings ['registration_page_icons']) ? 'above' : $settings ['registration_page_icons'])
  );

  $form ['oneall_social_login_settings_registration_page'] ['registration_page_caption'] = array(
    '#type' => 'textfield',
    '#title' => t('Social Login Icons: Caption [Leave empty for none]'),
    '#default_value' => (!isset($settings ['registration_page_caption']) ? t('Register with:') : $settings ['registration_page_caption']),
    '#size' => 60,
    '#maxlength' => 60,
    '#description' => t('This is the title displayed above the social network icons.')
  );


  $form ['oneall_social_login_settings_profile_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Edit Profile Page Settings'),
  );

  $form ['oneall_social_login_settings_profile_page'] ['profile_page_icons'] = array(
    '#type' => 'select',
    '#title' => t('Social Login Icons'),
    '#description' => t('Allows the users to link a social network account to their  regular account.'),
    '#options' => array(
      'above' => t('Show the Social Login icons above the profile settings'),
      'below' => t('Show the Social Login icons below the profile settings (Default, recommended)'),
      'disable' => t('Do not show the Social Login icons on the profile page')
    ),
    '#default_value' => (empty($settings ['profile_page_icons']) ? 'below' : $settings ['profile_page_icons'])
  );

  $form ['oneall_social_login_settings_profile_page'] ['profile_page_caption'] = array(
    '#type' => 'textfield',
    '#title' => t('Social Login Icons: Caption [Leave empty for none]'),
    '#default_value' => (!isset($settings ['profile_page_caption']) ? t('Link your account to a social network:') : $settings ['profile_page_caption']),
    '#size' => 60,
    '#maxlength' => 60,
    '#description' => t('This is the title displayed above the social network icons.')
  );


  //Enable the social networks/identity providers
  $form ['oneall_social_login_providers'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enable the social networks/identity providers of your choice'),
  );

  //Add providers
  foreach ($oneall_social_login_available_providers as $key => $provider_data) {
    $form ['oneall_social_login_providers'] ['oneall_social_login_icon_' . $key] = array(
      '#title' => htmlspecialchars($provider_data ['name']),
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'oneall_social_login_provider',
          'oneall_social_login_provider_' . $key,
        ),
        'style' => array(
          'float: left;',
          'margin: 5px;',
        ),
      ),
    );

    $form ['oneall_social_login_providers'] ['provider_' . $key] = array(
      '#type' => 'checkbox',
      '#title' => htmlspecialchars($provider_data ['name']),
      '#default_value' => (empty($settings ['provider_' . $key]) ? 0 : 1),
      '#attributes' => array(
        'style' => array(
          'margin: 15px;',
        ),
      ),
    );

    $form ['oneall_social_login_providers'] ['clear_' . $key] = array(
      '#type' => 'container',
      '#attributes' => array(
        'style' => array(
          'clear: both;',
        ),
      ),
    );
  }

  //Submit Button
  $form ['#submit'] [] = 'oneall_social_login_admin_settings_submit';
  $form ['actions'] = array(
    '#type' => 'actions'
  );
  $form ['actions'] ['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Callback Handler to verify the API Settings
 */
function oneall_social_login_admin_ajax_check_api_connection_callback($form, &$form_state) {
  //Message to be shown

  $error_message = '';
  $success_message = '';

  //Some fields are empty
  if (empty($_POST ['api_subdomain']) OR empty($_POST ['api_key']) OR empty($_POST ['api_secret'])) {
    $error_message = t('Please fill out each of the fields above');
  }
  //All fields filled out
  else {
    //Wrapper for full domains
    $api_subdomain = trim(drupal_strtolower($_POST ['api_subdomain']));
    if (preg_match("/([a-z0-9\-]+)\.api\.oneall\.com/i", $api_subdomain, $matches)) {
      $api_subdomain = $matches [1];
    }

    //Wrong syntax
    if (!preg_match("/^[a-z0-9\-]+$/i", $api_subdomain)) {
      $error_message = t('The subdomain has a wrong syntax! Have you filled it out correctly? <a href="@oneall_dashboard" target="_blank">Click here to create and view your API Credentials</a>', array(
        '@oneall_dashboard' => 'https://app.oneall.com/'
      ));
    }
    //Syntax seems to be OK
    else {
      //Build API Settings domain
      $api_domain = $api_subdomain . '.api.oneall.com';
      $api_key = $_POST ['api_key'];
      $api_secret = $_POST ['api_secret'];

      //Check
      $curl = curl_init();
      curl_setopt($curl, CURLOPT_URL, 'https://' . $api_domain . '/tools/ping.json');
      curl_setopt($curl, CURLOPT_HEADER, 0);
      curl_setopt($curl, CURLOPT_USERPWD, $api_key . ":" . $api_secret);
      curl_setopt($curl, CURLOPT_TIMEOUT, 15);
      curl_setopt($curl, CURLOPT_VERBOSE, 0);
      curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
      curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, 0);
      curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, 0);
      curl_setopt($curl, CURLOPT_FAILONERROR, 0);
      if (($json = curl_exec($curl)) === FALSE) {
        curl_close($curl);
        $error_message = t('Could not contact API. Your firewall probably blocks outoing requests on port 443');
      }
      else {
        $http_code = curl_getinfo($curl, CURLINFO_HTTP_CODE);
        curl_close($curl);

        if ($http_code == 401) {
          $error_message = t('The API credentials are wrong! <a href="@oneall_dashboard" target="_blank">Click here to create and view your API Credentials</a>', array(
            '@oneall_dashboard' => 'https://app.oneall.com/'
          ));
        }
        elseif ($http_code == 404) {
          $error_message = t('The subdomain does not exist. Have you filled it out correctly? <a href="@oneall_dashboard" target="_blank">Click here to create and view your API Credentials</a>', array(
            '@oneall_dashboard' => 'https://app.oneall.com/'
          ));
        }
        elseif ($http_code == 200) {
          $success_message = t('The settings are correct - do not forget to save your changes!');
        }
      }
    }
  }

  //Error
  if (!empty($success_message)) {
    return '<div id="oneall_social_login_check_api_result" class="messages status">' . $success_message . '</div>';
  }
  else {
    return '<div id="oneall_social_login_check_api_result" class="messages warning">' . (empty($error_message) ? 'Unknown error' : $error_message) . '</div>';
  }
}

/**
 * Saves the administration area settings
 */
function oneall_social_login_admin_settings_submit($form, &$form_state) {

  form_state_values_clean($form_state);

  //Parse Values
  foreach ($form_state ['values'] as $key => $value) {
    if (is_array($value) && isset($form_state ['values'] ['array_filter'])) {
      $value = array_keys(array_filter($value));
    }

    //Save this setting
    oneall_social_login_admin_settings_submit_set_option($key, $value);
  }

  drupal_set_message(t('The configuration options have been saved.'));
  cache_clear_all();
  menu_rebuild();
}

/**
 * Saves one administration area setting
 */
function oneall_social_login_admin_settings_submit_set_option($setting, $value) {

  if (!empty($setting)) {
    db_delete('oneall_social_login_settings') ->condition('setting', $setting) ->execute();
    db_insert('oneall_social_login_settings') ->fields(array(
      'setting' => $setting,
      'value' => $value
    )) ->execute();
  }
}

/**
 * Returns the oneall_social_login Settings
 */
function oneall_social_login_admin_get_settings() {

  //Container
  $settings = array();

  //Read settings
  $results = db_query("SELECT setting, value FROM {oneall_social_login_settings}");
  foreach ($results as $result) {
    $settings [$result ->setting] = $result ->value;
  }

  //Done
  return $settings;
}
