# ProjectSpyder Interface Specification

Specification of the ProjectSpyder Interface for clients.

## Find the server

There is no practical way to locate a ProjectSpyder server at the moment.
This is why you need to give the user the ability to enter in the hostname/ip address of the server.
You should default the hostname to `SpyderHub`, as this is also the default hostname of the server.
Maybe you need to append the local domain, e.g. `SpyderHub.localdomain` or `SpyderHub.fritz.box`.

## Communicate with the server

All communication is done using HTTP requests.
We support both, HTTP GET and POST requests.
If data from both is available at the same time,
then POST data is preferred.

## Pair client

Before first interaction, a client needs to be paired.
For this, the client needs to talk to `pair.php`.

As parameters, you only need to send the client's type.

The server will then supply you with the authcode, 
which you can use to interact with the server.

## Interact with the server

`interact.php` is used to interact with the server.
This can be used to send and to retrieve data.

The parameters are the following:
You need to send your authcode, your client's type and your requesttype.
Depending on your requesttype, you will need to send additional data.

Currently there are 2 requesttypes:

requesttype | Description
----------- | -----------
`GET` | Acquire all saved data.
`PUT` | Set the entire saved data, overwrites everything on the server.
`UPDATE` | Update saved data, merging new data with already the already existing data on the server. On conflict, existing data gets overwritten.

There will be more requesttypes in the future, as the system gets more complex.

## Syntax

After the HTML header, a ProjectSpyder response will follow its own syntax.

The response starts with `#START`.
If `#START` is not there, something went miserably wrong.

After that, there maybe is a `#DEBUG` section.
Anything within the `#DEBUG` section should be available for a developer or even the user, 
so that he can find out what went wrong.
A good way would be to output this section entirely to the serial console.
You don't need to interpret this section, as you will have another way of detection failures.

Then follows the `#DATA` section.
This section contains all of the important response data.
It is formatted in JSON.
The parameters of your device are saved in a nested object within the JSON response named `data`.

For conclusion, the response will end with `#END`.

## How `data` works

`data` contains an accurate description of the clients current properties.
This needs to be JSON formatted and needs to follow following rules:
The `data` must follow the global definition.
The `data` must not contain any HTML relevant characters, e.g. ` : / # `.

___TODO:__ add global definition_

## requesttimeout

With every request, your answer will contain a variable named `requesttimeout`.
This value defines the amount of time in seconds you at least need to wait until the next request.
You may break this rule, if you need your data updated for UX quality purposes.
(e.g. a button gets pressed)

## JSON `data`

Syntax:
```
{
	"settings": {
		"SettingName1": "Value1",
		"SettingName2": "Value2",
		"SettingName3": "Value3",
		
	},
	"data": {
		"VarName1": "Value1",  //raw data
		"VarName2": "Value2",  
		"VarName3": "Value3",
		"VarName4": "Value4",
		"VarName5": "Value5",
	},
	"usermodifiabledata": ["VarName1", "VarName2"],
	"friendly": {
		"settingsvar": {
			"SettingName1": "Setting 1",
			"SettingName2": "Setting 2",
		},
		"datavar": {
			"VarName1": "Variable 1",
			"VarName2": "Variable 2",
		},
		"datavalue": {
			"VarName1": "Wert 1",
			"VarName2": "Wert 2",
		},
		"type": "Type",
	},
	"preferredupdatetime": 10,  //preferred update time in s, you still must obey requesttimeout
	"device": {   //system protected info about this client
		"type": "type", 
		"name": "Name",
	},
}
```


Field | Description
----- | -----------
`data` | This contains all the raw data of this client, which the system uses to compare values. The format of the values is internal variable name and the raw value.
`settings` | This contains setting values of this client. This isn't needed, but if there is anything to configure on the client, this should be provided. These values will be directly editable by the user.
`preferredupdatetime` | This contains the preferred updatetime of the client. This will influence the systems decision of the `requesttimeount`. You still must follow the rules of `requesttimeout`! This value is in seconds, please decide upon a high value, preferably above 10 seconds, to not overload the system. As per `requesttimeout` guidelines, you can still send data upon user interaction with the client. Please read the `requesttimeout` paragraph for more information.
`usermodifiabledata` | This contains an array of internal `data` variable names, which the user is allowed to edit. Pure actors should include all their `data` variables, and combined sensor and actors can define which values are "outputs".
`friendly`: | Following values describe nested objects of `friendly`. Everything in `friendly` is used for the GUI to provide a userfriendly interface
`type` | The type only contains a String (preferrably as few words as possible) to describe the clients device type to the user. E.g. a type `button` would be `Button` and `temperature` would be `Temperature Sensor`
`datavar` | This contains userfriendly names of the `data` variable names. The format is internal variable name and the userfriendly variable name.
`datavalue` | This contains userfriendly variants of the `data` variable values. The format is internal variable name and the userfriendly value of that variable. E.g. a humidity of 0.5 would be 50%.
`settingsvar` | This contains userfriendly variants of the `settings` variable names. The format is settings variable name and a friendly name for this setting. This will only change what is displayed in front if the input field, so the user knows what he is changing.
`device` | All nested objects contain system protected data of your sensor. This includes your type and the user assigned name of your client. More values will be available for you soon. You cannot overwrite these values.

Every of those values can be left undefined and defaults will be assumed where needed.
We recommend to define `data` variables and highly encourage you to provide according userfriendly names.
Also we recommend you to define a userfriendly type.
If your client has no settings, you can leave the `settings` part away.

## Error, errors, errors!

You should not interpret the `#DEBUG` section!
In case of an error, you will get an `error` variable in the `#DATA` JSON response.
This will contain a short string of information about the error.

Expected errors:

Error | Description | Solution
----- | ----------- | --------
AUTHFAILED          | Your authcode is not valid. | Pair up again.
TYPEMISMATCH        | Your client's type doesn't match the authcode associated device. | Pair up again.
JSONINVALID         | The sent JSON is not deserializable by the server. | Check the JSON for correct formatting.
REQUESTTYPEINVALID  | The requesttype sent is not recognized by the system | Check for Syntax or ask user to update the system.

On other errors, wait and try again once a day.
