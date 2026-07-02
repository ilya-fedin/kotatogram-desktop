/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

class History;
class PhotoData;
class DocumentData;
struct FilePrepareResult;

namespace Data {
struct InputVenue;
class LocationPoint;
} // namespace Data

namespace MTP {
class Error;
} // namespace MTP

namespace Main {
class Session;
} // namespace Main

namespace Api {

struct MessageToSend;
struct SendAction;

void SendWebDocument(
	MessageToSend &&message,
	not_null<DocumentData*> document,
	std::optional<MsgId> localMessageId = std::nullopt,
	Fn<void()> doneCallback = nullptr,
	bool forwarding = false);

void SendExistingDocument(
	MessageToSend &&message,
	not_null<DocumentData*> document,
	std::optional<MsgId> localMessageId = std::nullopt,
	Fn<void()> doneCallback = nullptr,
	bool forwarding = false);

void SendExistingPhoto(
	MessageToSend &&message,
	not_null<PhotoData*> photo,
	std::optional<MsgId> localMessageId = std::nullopt,
	Fn<void()> doneCallback = nullptr,
	bool forwarding = false);

bool SendDice(
	MessageToSend &message,
	Fn<void(const MTPUpdates &, mtpRequestId)> doneCallback = nullptr,
	bool forwarding = false);

// We can't create Data::LocationPoint() and use it
// for a local sending message, because we can't request
// map thumbnail in messages history without access hash.
void SendLocation(SendAction action, float64 lat, float64 lon);

void SendVenue(SendAction action, Data::InputVenue venue);

void FillMessagePostFlags(
	const SendAction &action,
	not_null<PeerData*> peer,
	MessageFlags &flags);

void SendConfirmedFile(
	not_null<Main::Session*> session,
	const std::shared_ptr<FilePrepareResult> &file);

void SendLocationPoint(
	const Data::LocationPoint &data,
	const SendAction &action,
	Fn<void()> done,
	Fn<void(const MTP::Error &error)> fail);

} // namespace Api
