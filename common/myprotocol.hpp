// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#ifndef COMMON_MYPROTOCOL_HPP_
#define COMMON_MYPROTOCOL_HPP_

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

struct SignInPkg {
};
struct SignOutPkg {
};
struct RegistrationPkg {
};
struct RequestOnlineUsersPkg {
};
struct PingPkg {
};
struct PongPkg {
};

struct ResponseOnlineUsers {
    std::uint8_t OnlineUsers[UserNameLength][ResponseOnlineUsersCount];
    std::uint8_t IsEnd;
};


struct ControlSum {
    std::uint16_t CRC16;
};

union PkgContent {
    SignInPkg signInPkg;
    SignOutPkg signOutPkg;
    RegistrationPkg registrationPkg;
    ResponseOnlineUsers responseOnlineUsers;
    RequestOnlineUsersPkg requestOnlineUsersPkg;
    MessagePkg messagePkg;
    PingPkg pingPkg;
    PongPkg pongPkg;
};

struct MyProtocolPkg {
    Header Head;
    PkgContent Content;
    ControlSum CS;
};

#pragma pack(pop)

#endif // COMMON_MYPROTOCOL_HPP_
