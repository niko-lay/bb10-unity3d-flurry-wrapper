//
//  Flurry
//
//  Copyright (c) 2013 Flurry Inc. All rights reserved.
//

#ifndef FLURRYC_H_
#define FLURRYC_H_
/*!
 * 	@defgroup FlurryAnalytics Flurry Analytics C Interface
 *  @brief Provides all available methods for defining and reporting Analytics from use
 *  of your app.
 *
 *  Set of methods that allow developers to capture detailed, aggregate information
 *  regarding the use of their app by end users.
 *
 *  @note This class provides methods necessary for correct function of FlurryC.h.
 *  For information on how to use Flurry's Analytcs SDK to understand your users'
 *  behavior see <a href="http://support.flurry.com/index.php?title=Analytics">Support Center - Analytics</a>.
 *
 *  @author 2009 - 2013 Flurry, Inc. All Rights Reserved.
 *  @version 2.0.0
 * 	@{
 */

#ifdef __cplusplus
extern "C" {
#endif


/** @name Pre-Session Calls
 *  Optional sdk settings that should be called before start session.
 */
//@{

/*!
 *  @brief Explicitly specifies the App Version that Flurry will use to group Analytics data.
 *  @since 1.0
 *
 *  This is an optional method that overrides the App Version Flurry uses for reporting. Flurry will
 *  use the Package in your BAR xml file when this method is not invoked.
 *
 *  @note There is a maximum of 605 versions allowed for a single app. \n
 *  This method must be called prior to invoking #flurry_start_session().
 *
 *  @param aVersion The custom version name.
 */

 void flurry_set_app_version(const char *aVersion);

 /*!
  *  @brief Retrieves the Flurry Agent Build Version.
  *  @since 1.0
  *
  *  This is an optional method that retrieves the Flurry Agent Version the app is running under.
  *  It is most often used if reporting an unexpected behavior of the SDK to <a href="mailto:blackberrysupport@flurry.com">
  *  Flurry Support</a>
  *
  *  @note This method must be called prior to invoking #flurry_start_session(). \n
  *  FAQ for the BlackBerry SDK is located at <a href="http://wiki.flurry.com/index.php?title=BlackBerry_FAQ">
  *  Support Center - BlackBerry FAQ</a>.
  *
  *  @see #flurry_set_debug_log_enabled() for information on how to view debugging information on your console.
  *
  *  @return The agent version of the Flurry SDK.
  *
  */

 int flurry_get_flurry_agent_version();

 /*!
  *  @brief Displays an exception in the debug log if thrown during a Session.
  *  @since 1.0
  *
  *  This is an optional method that augments the debug logs with exceptions that occur during the session.
  *  You must both capture exceptions to Flurry and set debug logging to enabled for this method to
  *  display information to the console. The default setting for this method is @c false.
  *
  *  @note This method must be called prior to invoking #flurry_start_session().
  *
  *  @see #flurry_set_debug_log_enabled() for information on how to view debugging information on your console. \n
  *  #flurry_log_error() for details on logging errors and exceptions \n
  *
  *  @param anEnabled @c true to show errors in debug logs, @c false to omit errors in debug logs.
  */

 void flurry_set_show_error_in_log_enabled(int anEnabled);

 /*!
  *  @brief Generates debug logs to console.
  *  @since 1.0
  *
  *  This is an optional method that displays debug information related to the Flurry SDK.
  *  display information to the console. The default setting for this method is @c false.
  *
  *  @note This method must be called prior to invoking #flurry_start_session().
  *
  *  @param anEnabled @c true to show debug logs, @c false to omit debug logs.
  *
  */

 void flurry_set_debug_log_enabled(int anEnabled);

 /*!
  *  @brief Set the timeout for expiring a Flurry session.
  *  @since 1.0
  *
  *  This is an optional method that sets the time the app may be in the background before
  *  starting a new session upon resume.  The default value for the session timeout is 10
  *  seconds in the background.
  *
  *  @note This method must be called prior to invoking #flurry_start_session().
  *
  *  @param seconds The time in seconds to set the session timeout to.
  */

 void flurry_set_session_continue_seconds(int seconds);

 /*!
  *  @brief Send data over a secure transport.
  *  @since 3.0
  *
  *  This is an optional method that sends data over an SSL connection when enabled. The
  *  default value is @c false.
  *
  *  @note This method must be called prior to invoking #flurry_start_session().
  *
  *  @param anEnabled @c true to send data over secure connection.
  */

 void flurry_set_secure_transport_enabled(int anEnabled);

//@}



 /*!
  *  @brief Start a Flurry session for the project denoted by @c anAPIKey.
  *  @since 1.0
  *
  *  This method serves as the entry point to Flurry Analytics collection.  It must be
  *  called on application start passing in the launch options parameters.
  *  (single key string has corresponding value string).
  *  The session will continue
  *  for the period the app is in the foreground until your app is backgrounded for the
  *  time specified in #flurry_set_session_continue_seconds(). If the app is resumed in that period
  *  the session will continue, otherwise a new session will begin.
  *
  *  @note If testing on a simulator, please be sure to send App to background via gesture
  *  Flurry depends on the BlackBerry lifecycle to be complete for full reporting.
  *
  * @see #flurry_set_session_continue_seconds() for details on setting a custom session timeout.
  *
  * @param anAPIKey The API key for this project.
  * @param anOptionKeys passed custom launch options keys
  * @param anOptionValues passed custom launch options values
  * @param anOptionCount number of passed custom launch options, number of values and keys should be equal to anOptionCount

  */

 void flurry_start_session(const char *anAPIKey, const char **anOptionKeys, const char **anOptionValues, int anOptionCount);


 /*!
  *  @brief Records errors or exceptions that occur in your app
  *  @since 1.0
  *
  *  This method captures error or exception for reporting to Flurry. If anException is provided it is registered as exception kind, otherwise as error kind
  *
  *  @param anError Name of the error.
  *  @param aMessage The message to associate with the error.
  *  @param anException The exception object to report.
  */

 void flurry_log_error(const char *anError, const char *aMessage, const char *anException);


 /*!
  *  @brief Records an event occurrence (optionally timed) specified by @c anEventName.
  *  @since 1.0
  *
  *  This method allows you to capture event occurrences and optionally the length of an event. This can
  *  be extremely valuable to understand the level of engagement with a particular action. For
  *  example, you can capture how long a user spends on a level or reading an article.
  *
  *  @note You should not pass private or confidential information about your users in a
  *  custom event. \n
  *  Where applicable, you should make a concerted effort to use parameters with your timed
  *  events (#flurry_log_event_with_params(const char *, int, const char **, const char **, int)).
  *  This provides valuable information around the characteristics of an action (e.g. - Buy Event
  *  that has a Parameter of Widget with Value Golden Sword).
  *
  *  @see #flurry_log_event_with_params(const char *, int, const char **, const char **, int) for details on storing timed events with parameters. \n
  *  #flurry_end_timed_event() for details on stopping a timed event and (optionally) updating
  *  parameters.
  *
  *  @code
  *  static void start_level()
  {
  	 flurry_log_event("Level Played", 1);
  // Start user on level
  }

  static void end_level()
  {
  	 flurry_end_timed_event("Level Played", NULL, NULL, 0);
  // User done with level
  }
  *  @endcode
  *
  *  @param anEventName Name of the event. For maximum effectiveness, we recommend using a naming scheme
  *  that can be easily understood by non-technical people in your business domain.
  *  @param aTimed Specifies the event will be timed.
  */

 void flurry_log_event(const char *anEventName, int aTimed);

 /*!
  *  @brief Records a custom parameterized timed event specified by @c anEventName with @c aParameters.
  *  @since 1.0
  *
  *  This method overrides #flurry_log_event() to allow you to capture the length of an event with parameters.
  *  This can be extremely valuable to understand the level of engagement with a particular action
  *  and the characteristics associated with that action. For example, you can capture how long a user
  *  spends on a level or reading an article. Parameters can be used to capture, for example, the
  *  author of an article or if something was purchased while on the level.
  *
  *  @note You should not pass private or confidential information about your users in a
  *  custom event.
  *
  *  @see #flurry_end_timed_event() for details on stopping a timed event and (optionally) updating
  *  parameters.
  *
  *  @code
  *  static void start_level()
  {
  	 const char *aParamKeys= {"coins"};
  	 const char *aParamValues= {"100"};

  	 flurry_log_event_with_params("Level Played", 1, aParamKeys, aParamValues , 1);
  // Start user on level
  }

  static void end_level()
  {
  	 const char *aParamKeys= {"coins"};
  	 const char *aParamValues= {"200"};
  	 flurry_end_timed_event("Level Played",  aParamKeys, aParamValues , 1);
  // User done with level
  }
  *  @endcode
  *
  *  @param anEventName Name of the event. For maximum effectiveness, we recommend using a naming scheme
  *  that can be easily understood by non-technical people in your business domain.
  *  @param aTimed Specifies the event will be timed.
  *  @param aParamKeys  parameters keys.
  *  @param aParamValues parameters values.
  *  @param aParamCount a number of parameters.
  */

 void flurry_log_event_with_params(const char *anEventName, int aTimed, const char **aParamKeys, const char **aParamValues, int aParamCount);

 /*!
  *  @brief Ends a timed event specified by @c anEventName and optionally updates parameters with @c aParameters.
  *  @since 1.0
  *
  *  This method ends an existing timed event.  If parameters are provided, this will overwrite existing
  *  parameters with the same name or create new parameters if the name does not exist in the parameter
  *  map set by #flurry_log_event_with_params(const char *, int, const char **, const char **, int)
  *
  *  @note You should not pass private or confidential information about your users in a
  *  custom event. \n
  *  If the app is backgrounded prior to ending a timed event, the Flurry SDK will automatically
  *  end the timer on the event. \n
  *  #flurry_end_timed_event(const char *, const char **, const char **, int) is ignored if called on a previously
  *  terminated event.
  *
  *  @see #flurry_log_event_with_params(const char *, int, const char **, const char **, int) for details on starting a timed event with parameters.
  *
  *  @code
  *  static void start_level()
  {
  	 const char *aParamKeys= {"coins"};
  	 const char *aParamValues= {"100"};

  	 flurry_log_event_with_params("Level Played", 1, aParamKeys, aParamValues , 1);
  // Start user on level
  }

  static void end_level()
  {
  	 const char *aParamKeys= {"coins"};
  	 const char *aParamValues= {"200"};
  	 flurry_end_timed_event("Level Played",  aParamKeys, aParamValues , 1);
  // User done with level
  }
  *  @endcode
  *
  *  @param anEventName Name of the event. For maximum effectiveness, we recommend using a naming scheme
  *  that can be easily understood by non-technical people in your business domain.
  *  @param aParamKeys  parameters keys.
  *  @param aParamValues parameters values.
  *  @param aParamCount a number of parameters.
  */

 void flurry_end_timed_event(const char *anEventName, const char **aParamKeys, const char **aParamValues, int aParamCount);


/** @name User Info
 *  Methods to set user information.
 */
//@{

 /*!
  *  @brief Assign a unique id for a user in your app.
  *  @since 1.0
  *
  *  @note Please be sure not to use this method to pass any private or confidential information
  *  about the user.
  *
  *  @param aUserID The app id for a user.
  */
 void flurry_set_user_id(const char *aUserID);

 /*!
  *  @brief Set your user's age in years.
  *  @since 1.0
  *
  *  Use this method to capture the age of your user. Only use this method if you collect this
  *  information explicitly from your user (i.e. - there is no need to set a default value).
  *
  *  @note The age is aggregated across all users of your app and not available on a per user
  *  basis.
  *
  *  @param anAge Reported age of user.
  *
  */

 void flurry_set_age(int anAge);

 /*!
  *  @brief Set your user's gender.
  *  @since 1.0
  *
  *  Use this method to capture the gender of your user. Only use this method if you collect this
  *  information explicitly from your user (i.e. - there is no need to set a default value). Allowable
  *  values are @c @"M" or @c @"F"
  *
  *  @note The gender is aggregated across all users of your app and not available on a per user
  *  basis.
  *
  *  @param aGender Reported gender of user.
  *
  */

  void flurry_set_gender(const char *aGender);

  //@}

  /** @name Location Reporting
   *  Methods for setting location information.
  */
  //@{
  /*!
  *  @brief Set the location of the session.
  *  @since 1.0
  *
  *  Use information from the BlackBerry location API to specify the location of the session. Flurry does not
  *  automatically track this information or uses location API.
  *
  *  @note Only the last location entered is captured per session. \n
  *  Regardless of accuracy specified, the Flurry SDK will only report location at city level or higher. \n
  *  Location is aggregated across all users of your app and not available on a per user basis. \n
  *  This information should only be captured if it is germaine to the use of your app.
  *
  *  @param aLatitude The latitude.
  *  @param aLongitude The longitude.
  *  @param aHorizontalAccuracy The radius of uncertainty for the location in meters.
  *  @param aVerticalAccuracy The accuracy of the altitude value in meters.
  *
  */

  void flurry_set_location(double aLatitude, double aLongitude, float aHorizontalAccuracy, float aVerticalAccuracy);

  //@}

  /** @name Session Reporting Calls
   *  Optional methods that can be called at any point to control session reporting.
   */
  //@{

  /*!
   *  @brief Set session to report when app closes.
   *  @since 1.0
   *
   *  Use this method report session data when the app is closed. The default value is @c true.
   *
   *  @see #flurry_set_session_reports_on_pause_enabled()
   *
   *  @param aSendSessionReportsOnClose true to send on close, false to omit reporting on close.
   *
   */

  void flurry_set_session_reports_on_close_enabled(int aSendSessionReportsOnClose);

  /*!
   *  @brief Set session to report when app is sent to the background.
   *  @since 1.0
   *
   *  Use this method report session data when the app is paused. The default value is @c false.
   *
   *  @param aSessionReportsOnPauseEnabled true to send on pause, false to omit reporting on pause.
   *
   */

  void flurry_set_session_reports_on_pause_enabled(int aSessionReportsOnPauseEnabled);

  /*!
   *  @brief Enable custom event logging.
   *  @since 1.0
   *
   *  Use this method to allow the capture of custom events. The default value is @c true.
   *
   *  @param aSetEventLoggingEnabled true to enable event logging, false to stop custom logging.
   *
   */

 void flurry_set_event_logging_enabled(int aSetEventLoggingEnabled);


 //@}

#ifdef __cplusplus
}
#endif

//@}

#endif /* FLURRYC_H_ */
