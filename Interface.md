# ProjectSpyder Interface Specification

Specification of the ProjectSpyder Interface for clients.

## Find the server

There is no practical way to locate a ProjectSpyder server at the moment.
This is why you need to give the user the ability to enter in the hostname/ip address of the server.
You should default the hostname to `SpyderHub`, as this is also the default hostname of the server.
Maybe you need to append the local domain, e.g. `SpyderHub.fritz.box`.

## Communicate with the server

All communication is done using HTTP requests.
We currently only support HTTP GET requests.


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
`GET` | Used for actors to acquire their state, which they are supposed to follow.
`PUT` | Used for sensors ro send their current state to the server.

There will be more requesttypes in the future, as the system gets more complex.

## How states work

A `state` is an accurate description of the clients current properties.
This can be any string, as long as some rules are followed:
The `state` must not contain any HTML relevant characters, e.g. ` : / # `.
The `state` must follow the global definition of the `type`, if you are not using the type `raw`.

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
It is formatted like this: `[VarName]=>Value`, one per line.

For conclusion, the response will end with `#END`.

## requesttimeout

With every request, your answer will contain a variable named `requesttimeout`.
This value defines the amount of time in seconds you at least need to wait until the next request.
You may break this rule, if you are an sensor, which needs their state updated for UX quality purposes.
(e.g. a button gets pressed)

## The type `raw`

`raw` is a special type, as it allows the client to use any string as their state.
The UI will allow the user to directly edit this string.

## Error, errors, errors!

You should not interpret the `#DEBUG` section!
In case of an error, you will get an `error` variable in your `#DATA` section.
This will contain a short string of information about the error.

Expected errors:
Error | Description | Solution
----- | ----------- | --------
AUTHFAILED | You will get this error, if your authcode is not valid. | Just go ahead and request a new one.
TYPEINVALID | You will get this error, if your client's type doesn't match the authcode associated device. | Just pair up again.

On other errors, wait and try again once a day.