//
// Created by w1ckedente on 13.11.2020.
//

#ifndef CRYPTO_MESSENGER_MYPROTOCOL_HPP
#define CRYPTO_MESSENGER_MYPROTOCOL_HPP

#include <cinttypes>
#include <myprotocoldefs.hpp>

#pragma pack(push, 1)

enum MyProtocolPkgType : std::uint8_t {
    PkgTypeSignIn,
    PkgTypeSignOut,
    PkgTypeRegistration,
    PkgTypeMessage,
    PkgTypeRequestOnlineUsers,
    PkgTypeResponseOnlineUsers,
    PkgPingPkg,
    PkgPongPkg
};

enum MyProtocolErrors : std::uint8_t {
    ErrSuccess,
    ErrExistUser,
    ErrAlreadySignIn,
    ErrBadUserData,
    ErrOfflineUser,
    ErrMismatchingVersions
};

struct Authorize {
    std::uint8_t UserName[UserNameLength];
    std::uint8_t Password[PasswordLength];
};

struct Header {
    std::uint8_t Signature[SignatureStringLength];
    std::uint8_t ProtocolVersion[VersionStringLength];
    MyProtocolPkgType Type;
    Authorize AuthorizeData;
    MyProtocolErrors Error;
};

struct MessagePkg {
    std::uint8_t DestUserName[UserNameLength];
    std::uint8_t Message[MessageLength];
};

struct SignInPkg {};
struct SignOutPkg {};
struct RegistrationPkg {};
struct RequestOnlineUsersPkg {};
struct PingPkg {};
struct PongPkg {};

struct ResponseOnlineUsers {
    std::uint8_t OnlineUsers[UserNameLength][ResponseOnlineUsersCount];
    std::uint8_t IsEnd;
};


struct ControlSum {
    std::uint16_t CRC16;
};

union PkgContent {
    SignInPkg;
    SignOutPkg;
    RegistrationPkg;
    ResponseOnlineUsers;
    RequestOnlineUsersPkg;
    MessagePkg;
    PingPkg;
    PongPkg;
};

struct MyProtocolPkg {
    Header Head;
    PkgContent Content;
    ControlSum CS;
};

#pragma pack(pop)

#endif //CRYPTO_MESSENGER_MYPROTOCOL_HPP