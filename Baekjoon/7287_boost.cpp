#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp> // JSON 라이브러리 포함

namespace beast = boost::beast;     // Boost.Beast 네임스페이스
namespace http = beast::http;      // HTTP 네임스페이스
namespace net = boost::asio;       // Boost.Asio 네임스페이스
using tcp = net::ip::tcp;          // TCP 네임스페이스
using json = nlohmann::json;

int main() {
    try {
        // API 요청 정보 설정
        std::string host = "solved.ac";
        std::string port = "443"; // HTTPS 포트
        //std::string target = "/api/v3/site/stats"; // 요청 URL
        std::string target = "/api/v3/account/verify_credentials";
        int version = 11; // HTTP 1.1

        // I/O Context 생성
        net::io_context ioc;

        // SSL 컨텍스트 생성
        net::ssl::context ctx(net::ssl::context::tls_client);

        // 인증서 경로 설정
        ctx.set_default_verify_paths();

        // 리졸버와 SSL 스트림 생성
        tcp::resolver resolver(ioc);
        beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

        // SNI 설정 (필요할 경우)
        if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str())) {
            throw beast::system_error(
                beast::error_code(
                    static_cast<int>(::ERR_get_error()),
                    net::error::get_ssl_category()),
                "Failed to set SNI hostname");
        }

        // 서버 이름과 포트를 사용해 TCP 연결
        auto const results = resolver.resolve(host, port);
        beast::get_lowest_layer(stream).connect(results);

        // SSL 핸드셰이크 수행
        stream.handshake(net::ssl::stream_base::client);

        // HTTP 요청 생성
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::content_type, "application/json");// Content-Type 헤더 (필요할 경우)
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set("x-solvedac-language", "ko");
        // 쿠키 추가
        std::string cookie_value = "solvedacToken=s\%3AeyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJoYW5kbGUiOiJjanc3ODIzIiwidG9rZW5WZXJzaW9uIjoyLCJpYXQiOjE3MzUxNzQ5NDB9.FpmP6iDnzSkt5wpwf4zu6ZcmbW8vXXVbzxGcth98P50.BXzKdGE%2Bihu\%2FahRGx3ggVujZk%2Bs6EwffZOheBvZNz2c"; // 쿠키 값 설정
        req.set(http::field::cookie, cookie_value);

        // 요청 전송
        http::write(stream, req);

        // 응답 수신
        beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);

        // 응답 출력
        //std::cout << "Response:\n" << res << std::endl;

        // 응답 본문을 JSON으로 파싱
        std::string body = beast::buffers_to_string(res.body().data()); // 본문을 문자열로 변환
        json parsed_json = json::parse(body); // JSON 파싱

        // JSON 데이터 출력
        std::cout << "Parsed JSON:" << std::endl;
        //std::cout << parsed_json.dump(4) << std::endl; // 보기 좋게 출력 (4-space indent)
        std::cout << parsed_json["user"]["solvedCount"] << std::endl;
        std::string userid = parsed_json["user"]["handle"].get<std::string>();
        std::cout << userid << std::endl;

        // SSL 종료
        beast::error_code ec;
        stream.shutdown(ec);
        if (ec == net::ssl::error::stream_truncated) {
            // 이 오류는 정상 종료의 일부로 발생할 수 있음
            ec = {};
        }
        if (ec) {
            throw beast::system_error{ec};
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
