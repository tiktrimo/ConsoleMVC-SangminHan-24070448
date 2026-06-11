# ConsoleMVC-SangminHan-24070448

> **[POC Stage]** 현재 개념 검증(Proof of Concept) 단계입니다. 구현 코드는 포함되지 않습니다.

## POC: MVC 스켈레톤 코드

반도체 시료 생산주문관리 시스템의 MVC 아키텍처 검증을 위한 PoC 레포지토리입니다.

## 목적

- Model / Controller / View 패키지 구조와 역할 분리 검증
- 콘솔 기반 인터페이스와 비즈니스 로직 분리 구조 확인

## 폴더 구조

```
src/
  model/       - 데이터 모델 (Sample, Order 등 도메인 객체)
  controller/  - 비즈니스 로직 처리
  view/        - 콘솔 UI 출력 및 입력 처리
```

## 역할 정의

| 레이어 | 역할 |
|--------|------|
| Model | 시료(Sample), 주문(Order) 등 도메인 객체 및 상태 관리 |
| Controller | 주문 접수·승인·거절, 생산라인 로직 처리 |
| View | 메인 메뉴, 시료 목록, 주문 화면 등 콘솔 출력 |
